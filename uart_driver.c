v25be9h3@system7:~/arm$ cat u1_driver.c
#include<lpc21xx.h>
#include"header.h"
void uart0_init(unsigned int baud)
{
int pclk,result=0;
if(VPBDIV==0X0)
pclk=15000000;
else if(VPBDIV==0X01)
pclk=60000000;
else if(VPBDIV==0x02)
pclk=30000000;
result=pclk/(16*baud);
PINSEL0|=0X00000005;
U0LCR=0X83;
U0DLL=result&0xff;
U0DLM=(result>>8)&0xff;
U0LCR=0X03;
}
//   TRANSMITER

#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
U0THR=data;
while(THRE==0);
}

// reciever

#define RDR (U0LSR&1)
unsigned char uart0_rx(){
while(RDR==0);
return U0RBR;
}
// string
void uart0_tx_string(char *ptr)
{
while(*ptr!=0)
{
uart0_tx(*ptr);
ptr++;
}
}

// recive a string using uart
