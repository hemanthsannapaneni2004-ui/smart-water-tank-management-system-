#include<lpc21xx.h>
#include"header.h"
int water_level(void)
{
        int adc_val2,w;
        adc_val2=adc_read(1);
        w=(adc_val2*100)/1023;
        return w;
}
