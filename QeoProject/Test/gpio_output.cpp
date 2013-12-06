#include "gnublin.h"

 
int main()
{
   gnublin_gpio gpio;
   printf("Running\n");
   gpio.pinMode(3,OUTPUT);
 
   while(1){
     gpio.digitalWrite(3,HIGH);
     sleep(2);
     printf("High\n");
     gpio.digitalWrite(3,LOW);
     printf("Low\n");
     sleep(2);
   }
}
