
#include<lpc21xx.h>
#include"header.h"
#define TRIG (1<<10)
#define ECHO (1<<11)
void ultrasonic_init(void)
{
IODIR0 |=TRIG;
IODIR0 &= ~ECHO;
}
unsigned int ultrasonic_read(void)
{
unsigned int count=0;
IOCLR0=TRIG;
delay_us(2);

IOSET0=TRIG;
delay_us(10);
IOCLR0=TRIG;

while(!(IOPIN0 & ECHO));
while(IOPIN0 & ECHO)
{
count++;
delay_us(1);
}
return(count/58);
}
