// #include <stdio.h>

// #define   SERIAL_DEV "/dev/ttyUSB0"
// #define SPEED 9600

// void read_port()
// {
//    int serial_fd = 0;
//    struct pollfd fds[1];
//    fds[0].fd = serial_fd;
//    fds[0].events = POLLIN ;
//    int pollrc = poll( fds, 1, 1000);
//    if (pollrc < 0)
//    {
//       perror("poll");
//    }
//    else if( pollrc > 0)
//    {
//       if( fds[0].revents & POLLIN )
//       {
//          char buff[1024];
//          ssize_t rc = read(serial_fd, buff, sizeof(buff) );
//          if (rc > 0)
//          {
//             /* You've got rc characters. do something with buff */
//             printf("%d\n", buff);
//          }
//          else
//          {
//             printf("0\n");
//          }
//       }
//    }
// }

// PI_THREAD (serialReader2)
// {
//    int fd ;
//    (void)piHiPri (10) ;

//    int i = 0;
//    while (1)
//    if (1)
//    {
//       printf("%d : buff = \n", i);
//       read_port();
//       i++;
//       sleep(1);
//    }
//    else
//    {
//       sleep(1);
//    }
//    return 0;
// }
