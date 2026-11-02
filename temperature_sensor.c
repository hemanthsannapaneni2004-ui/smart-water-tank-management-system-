
#include<lpc21xx.h>
#include"header.h"
float temperature(void)
{
        float adc_val,vout,temp;
        adc_val=adc_read(0);
        vout=(adc_val*3.3)/1023;
        temp=(vout/0.01)/10;
        return temp;
}
