v25be9h3@system7:~/arm$ cat  delay1.c
#include<lpc21xx.h>
#include"u1_header.h"
void delay_ms(unsigned int ms)
{
T0PR=15000-1;
T0TC=0;
T0PC=0;
T0TCR=1;
         while(T0TC<ms);
T0TCR=0;
}
