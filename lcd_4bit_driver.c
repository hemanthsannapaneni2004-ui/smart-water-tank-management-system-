v25be9h3@system7:~/arm$ cat  4bit_driver.c
#include<lpc21xx.h>
#include"header.h"
void lcd_data(unsigned char data)
{
int temp;
IOCLR1=0XFF<<16;
temp=((data&0xf0)<<16);
IOSET1=temp;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

IOCLR1=0XFF<<16;
temp=((data&0x0F)<<20);
IOSET1=temp;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}
void lcd_cmd(unsigned int cmd)
{
int temp;
IOCLR1=0XFF<<16;
temp=((cmd&0xf0)<<16);
IOSET1=temp;
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

IOCLR1=0XFF<<16;
temp=((cmd&0x0F)<<20);
IOSET1=temp;
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}
void lcd_init(void)
{

IODIR1=0XFF<<16;
IOCLR1=1<<19;
lcd_cmd(0x02);
lcd_cmd(0x28);
lcd_cmd(0x0E);
lcd_cmd(0x01);
lcd_cmd(0x03);
}
void lcd_string(char *ptr)
{
while(*ptr!=0)
{
lcd_data(*ptr);
ptr++;
}
}
