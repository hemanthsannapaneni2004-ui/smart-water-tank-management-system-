v25be9h3@system7:~/arm$ cat servo.c
#include<lpc21xx.h>
#include"header.h"
//#define SERVO (1<<7)
void servo_init(void)
{
        PINSEL0|=(1<<17);

        PWMPR=14;
        PWMMR0=20000;
        PWMMR4=1000;

        PWMMCR=(1<<1);
        PWMPCR=(1<<12);
        PWMLER=(1<<0)|(1<<4);
        PWMTCR=(1<<0)|(1<<3);
}
void servo_0(void)
{
PWMMR4=1000;
PWMLER=(1<<4);
}
void servo_90(void)
{
PWMMR4=1500;
PWMLER=(1<<4);

}
void servo_180(void)
{
PWMMR4=2000;
PWMLER=(1<<4);
}

void wall_operation(void)
{
servo_180();
uart0_tx_string("wall open\r\n");
delay_sec(3);
uart0_tx_string("wall closed\r\n");
servo_0();
}
