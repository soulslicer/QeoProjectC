    #include <stdio.h>   /* Standard input/output definitions */
    #include <stdlib.h>  /* exit */
    #include <string.h>  /* String function definitions */
    #include <unistd.h>  /* UNIX standard function definitions */
    #include <fcntl.h>   /* File control definitions */
    #include <errno.h>   /* Error number definitions */
    #include <termios.h> /* POSIX terminal control definitions */
    #include <ctype.h>   /* isxxx() */

    /* ------------------------------------------------------------------------

    cc -o 433 433.c

    Usage ./433 [option] ...

       -r, receiver (default)

       -t, transmitter

       -s BPS, bits per second, default 2400
          (300, 600, 1200, 1800, 2400, 4800, 9600, 19200)

       -m COUNT, test messages, default 1000

    ./433 -t -s4800 -m500 run as transmitter send 500 messages at 4800 bps
    ./433 -r -s4800       run as receiver (default), receive at 4800 bps

    -------------------------------------------------------------------------- */

    #define PREAMBLE 0x21
    #define SYNC     0xAA

    int     rx       = 1;     /* defaults to receiver end */
    int     messages = 1000;  /* default send 1000 test messages */
    speed_t speed    = B9600; /* default to 2400 bps */

    struct termios orig;
    int filedesc;

    /* prototypes */

    int  openSerialPort (char * device, int bps);
    void tx_message     (int fd, int mlen, char * dat);
    int  rx_message     (int fd, char * dat);
    int  initOpts       (int argc, char *argv[]);
    void tidyup(void);

    int main(int argc, char *argv[])
    {
       int i, c;
       char buf[512];

       initOpts(argc, argv);

       filedesc = openSerialPort("/dev/ttyAMA0", speed);

       if (filedesc == -1) exit(1);

       atexit(tidyup);

       if (rx)
       {
          while(1)
          {
             usleep(100);
             c = rx_message(filedesc, buf);
             if (c > 0)
             {
                buf[c]=0;
                printf(buf);
             }
          }
       }
       else
       {
          for (i=1; i<=messages; i++)
          {
             sprintf(buf, "message #%d\n", i);
             tx_message(filedesc, strlen(buf), buf);
             usleep(500); /* delay between messages */
          }
       }

    }

    void tidyup(void)
    {
       fflush(NULL); /* flush output */

       /* important to use TCSAFLUSH, otherwise buffered messages will be lost */
       tcsetattr(filedesc, TCSAFLUSH, &orig); /* restore original serial settings */
    }

    int openSerialPort(char * device, int bps)
    {
       int fd;
       struct termios new;
       char buf[128];

       fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);

       if (fd == -1)
       {
          sprintf(buf, "openSerialPort %s error", device);
          perror(buf);
       }
       else
       {
          tcgetattr(fd, &orig); /* save current serial settings */
          tcgetattr(fd, &new);
          cfmakeraw(&new);
          fprintf(stderr, "speed=%d\n", bps);
          cfsetispeed(&new, bps);
          cfsetospeed(&new, bps);
          tcsetattr(fd, TCSANOW, &new); /* set new serial settings */
          fcntl (fd, F_SETFL, O_RDWR);
       }
       return fd;
    }

    int checksum(int len, char * dat)
    {
       int cksm;
       int i;

       cksm = 0;
       for (i=0; i<len; i++)  cksm ^= dat[i];

       return cksm;
    }

    void tx_message(int fd, int mlen, char * dat)
    {
       char buf[300];
       char cksm;
       int wrote;

       buf[0] = SYNC; /* gives time for the receiving uart to sync */
       buf[1] = SYNC; /* gives time for the receiving uart to sync */
       buf[2] = PREAMBLE;
       buf[3] = mlen;

       memcpy(buf+4, dat, mlen);

       cksm = checksum(mlen+2, buf+2);
       buf[mlen+4] = cksm;

       wrote = write(fd, buf, mlen+5);
       if (wrote != (mlen+5)) printf("short write %d\n", wrote);
    }

    void printBuf(char * buf, int bufLen)
    {
       int i;

       for (i=0; i<bufLen; i++)
       {
          if (isprint(buf[i])) printf("%c ", buf[i]);
          else                 printf("%02X ", buf[i]);
       }

       printf("\n");
    }

    int rx_message(int fd, char * dat)
    {
       static int  posBuf=0;
       static char msgBuf[512];

       int i, scanning, mlen, validMessage;
       char cksm;
       char * ptr;

       validMessage = 0;

       i = read(fd, msgBuf+posBuf, sizeof(msgBuf)-posBuf);

       if (i>0)
       {
          posBuf += i;

          scanning = 1;

          while (scanning)
          {
             if (msgBuf[0] != PREAMBLE)
             {
                /* find message start */

                ptr = memchr(msgBuf, PREAMBLE, posBuf);

                if (ptr != NULL)
                {
                   /* preamble found, discard previous junk */

                   i = ptr - msgBuf;
                   posBuf -= i;
                   memmove(msgBuf, ptr, posBuf);
                }
                else
                {
                   /* no preamble found, discard junk */

                   posBuf = 0;
                   scanning = 0;
                }
             }

             if (posBuf > 2)
             {
                /* we have enough to calculate size */

                mlen = msgBuf[1];

                if (posBuf > (mlen+2))
                {
                   /* we have enough for a message */

                   cksm = checksum(mlen+2, msgBuf);

                   if (msgBuf[mlen+2] == cksm)
                   {
                      /* valid message received */
                      validMessage = 1;

                      /* copy message to callers buffer */
                      memmove(dat, msgBuf+2, mlen);

                      /* remove from receive buffer */
                      posBuf -= (mlen+3);
                      if (posBuf) memmove(msgBuf, msgBuf+mlen+3, posBuf);
                      scanning = 0;
                   }
                   else
                   {
                      /* corrupt message or invalid preamble.
                         Delete preamble and search for another
                      */
                      msgBuf[0] = 0;
                   }
                }
                else scanning = 0;
             }
             else scanning = 0;
          }
       }

       if (validMessage) return mlen; else return 0;

    }

    int initOpts(int argc, char *argv[])
    {
       int opt;

       while ((opt = getopt(argc, argv, "m:rs:t")) != -1)
       {
          switch (opt)
          {
             case 'm':
                opt = atoi(optarg);
                if (opt>0) messages = opt;
                break;

             case 'r':
                rx = 1;
                break;

             case 's':
                opt = atoi(optarg);

                if      (opt ==   300) speed =   B300;
                else if (opt ==   600) speed =   B600;
                else if (opt ==  1200) speed =  B1200;
                else if (opt ==  1800) speed =  B1800;
                else if (opt ==  2400) speed =  B2400;
                else if (opt ==  4800) speed =  B4800;
                else if (opt ==  9600) speed =  B9600;
                else if (opt == 19200) speed = B19200;

                break;

             case 't':
                rx = 0;
                break;
          }
       }
       return 0;
    }