}v25be9h3@system7:~/arm$ cat eeprom.c
#include<lpc21xx.h>
#include"header.h"
unsigned int add;
void epprom(unsigned char t)
{

        unsigned char temp;
        i2c_send(0xa0,add,t);
        delay_ms(30);
        temp=i2c_receive(0xa1,add++);
        if(temp==t)
        {
        uart0_tx_string("\r\n EEPROM STATUS :DATA SAVED\r\n");
        //uart0_tx(add/10+48);
        //uart0_tx(add%10+48);
        }
        else
        {
        uart0_tx_string("\r\n EEPROM STATUS : DATA NOT SAVED \r\n");
        //uart0_tx(add/10+48);
        //uart0_tx(add%10+48);
        }
        //add++;
}
