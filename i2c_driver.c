v25be9h3@system7:~/arm$ cat i2c_driver.c
/*i2c_driver.c*/

#include <LPC21xx.H>

#include "header.h"


void i2c_init(void){

        PINSEL0|=0x50;//P0.2-> SCL, P0.3-> SDA

        I2CONSET=(1<<6);//I2EN=1, AA=0 (Master mode selecte, I2C interface is enabled)

        I2SCLH=I2SCLL=75;//Std speed mode

}


#define SI ((I2CONSET>>3)&1)

void i2c_send(u8 sa, u8 mr, u8 data){

        /*step1: generate start condi*/

        I2CONSET=(1<<5);//STA=1

        I2CONCLR=(1<<3);//clear SI*

        while(SI==0);//waiting for start condi

                                                         //to generate

        I2CONCLR=(1<<5);//STA=0


        /*step2: send SA+W & check ack*/

        I2DAT=sa;//send SA+W

        I2CONCLR=(1<<3);//SI=0

        while(SI==0);

        if(I2STAT==0x20){

         uart0_tx_string("ERR: SA+W\r\n");

         goto exit;

        }


        /*step3: send mr addr & check ack*/

        I2DAT=mr;//send memory addr

        I2CONCLR=(1<<3);//SI=0

        while(SI==0);

        if(I2STAT==0x30){

         uart0_tx_string("ERR: Memory Addr\r\n");

         goto exit;

        }



        /*step4: send data & check ack*/

        I2DAT=data;//send data

        I2CONCLR=(1<<3);//SI=0

        while(SI==0);

        if(I2STAT==0x30){

         uart0_tx_string(" ");

         goto exit;

        }



        /*step5: generate stop condi*/

        exit:

                        I2CONSET=(1<<4);//STO=1

                        I2CONCLR=(1<<3);//clear SI*


}


u8 i2c_receive(u8 sa, u8 mr){

        u8 temp;

        /*step1: generate start condi*/

        I2CONSET=(1<<5);//STA=1

        I2CONCLR=(1<<3);//clear SI*

        while(SI==0);//waiting for start condi

                                                         //to generate

        I2CONCLR=(1<<5);//STA=0



        /*step2: send SA+W & check ack*/

        I2DAT=sa^1;//send SA+W

        I2CONCLR=(1<<3);//SI=0

        while(SI==0);

        if(I2STAT==0x20){

         uart0_tx_string("ERR: SA+W\r\n");

         goto exit;

        }



        /*step3: send mr addr & check ack*/

        I2DAT=mr;//send memory addr

        I2CONCLR=(1<<3);//SI=0

        while(SI==0);

        if(I2STAT==0x30){

         uart0_tx_string("ERR: Memory Addr\r\n");

         goto exit;

        }



        /*step4: generate restart condi*/

        I2CONSET=(1<<5);//STA=1

        I2CONCLR=(1<<3);//clear SI*

        while(SI==0);//waiting for start condi

                                                         //to generate

        I2CONCLR=(1<<5);//STA=0



        /*step5: send SA+R & check ack*/

        I2DAT=sa;//send SA+R

        I2CONCLR=(1<<3);

        while(SI==0);

        if(I2STAT==0x48){

                uart0_tx_string("ERR: SA+R\r\n");

                goto exit;

        }





        /*step6: read data from slave & send noack*/

        I2CONCLR=(1<<3);//SI=0

        while(SI==0);//waiting for data to receive

        temp=I2DAT;





        /*step7: generate stop condi*/

        exit:

                        I2CONSET=(1<<4);//STO=1

                        I2CONCLR=(1<<3);//clear SI*



        /*step8: return data*/

        return temp;

}
/*
int adress=0;
void read_rtc(void)
{
        unsigned char data[6];
        int i;
        data[0]= i2c_receive(0xD1,0x04);
        data[1]= i2c_receive(0xD1,0x05);
        data[2]= i2c_receive(0xD1,0x06);
        data[3]= i2c_receive(0xD1,0x02);
        data[4]= i2c_receive(0xD1,0x01);
        data[5]= i2c_receive(0xD1,0x00);

        for(i=0;i<6;i++)
        {
                i2c_send(0xa0,adress,data[i]);
                delay_ms(20);
                adress++;
        }
}

void print_rtc(void)
{
        unsigned char data[6];
        int i;
        int padress=0;
         while(padress<adress)
         {
        for(i=0;i<6;i++)
        {
                data[i]=i2c_recieve(0xa1,padress);
                delay_ms(20);
                padress++;
        }

                uart0_tx((day/0x10)+48);
                uart0_tx((day%0x10)+48);
                uart0_tx('/');
                uart0_tx((month/0x10)+48);
                uart0_tx((month%0x10)+48);
                uart0_tx('/');
                uart0_tx((year/0x10)+48);
                uart0_tx((year%0x10)+48);
                uart0_tx_string("\r\n");


        }
}

  */
        v25be9h3@system7:~/arm$ cat major_project.c
v25be9h3@system7:~/arm$ cat major_project.c
v25be9h3@system7:~/arm$ cat major_project.c
v25be9h3@system7:~/arm$ cat major_main.c
#include"header.h"
#include <LPC21xx.H>
extern int mode;
int t[6];
unsigned char flag=0;
int main()
{

                                        //int adc_value;
                                   // unsigned char t;
                                        u8 h,m,s,day,month,year;
                                        unsigned char clean_h;
                                        float temp;
                                //      float vout,adcout;
                                //      unsigned int can_data(2);
                                        unsigned int water,distance;
                                        IODIR0|=RED_LED|YELLOW_LED|GREEN_LED;
                                    IOSET0|=RED_LED|YELLOW_LED|GREEN_LED;


                                        uart0_init(9600);
                                        i2c_init();
                                        adc_init();
                                        lcd_init();
                                        servo_init();
                                        ultrasonic_init();
                                        config_for_eint0();

                                        //rtc  time
                                        i2c_send(0xD0,0x00,0x00);
                                        i2c_send(0xD0, 0x2, 0x65);//set hrs
                                        i2c_send(0xD0, 0x1, 0x50);//set mins
                                        i2c_send(0xD0, 0x0, 0x55);//set secs
                                        //RTC DATE
                                        i2c_send(0xD0, 0x04, 0x04);
                                        i2c_send(0xD0, 0x05, 0x10);
                                        i2c_send(0xD0, 0x06, 0x26);
                                //       uart0_tx_string("hi\r\n");
                                while(1)
                                {

                                        uart0_tx_string("\r\n---------------------------------------------------\r\n");
                                        uart0_tx_string("SMART WATER TANK MANAGEMENT \r\n");
                                        uart0_tx_string("---------------------------------------------------------\r\n");
                                        uart0_tx_string("controller:lpc2129 ARN7\r\n");
                                        uart0_tx_string("project status:RUNNING");


                                temp=temperature();
                                uart0_integer(temp);

                        //      water=water_level();
                        water=water_level();
                                uart0_integer(water);

                                distance=ultrasonic_read();
                                if(mode==1)
                                {
                                        uart0_tx_string("\r\n MANUAL MODE\r\n");
                                        if(water<20)
                                        {
                                                uart0_tx_string("alert!low water LEVEL!\r\n");
                                                uart0_tx_string("TURN ON THE MOTOR:");
                                                IOSET0|=RED_LED|YELLOW_LED;
                                                IOCLR0|=GREEN_LED;
                                                while(1)
                                                {
                                                        if(sw1==0)
                                                        {
                                                                while(sw1==0);
                                                                uart0_tx_string("\r\nPUMP STATUS : ON\r\n");
                                                                uart0_tx_string("\r\n RELAY STATUS:ON\r\n");
                                                                uart0_tx_string("\r\n VALUE STATUS :OPEN\r\n");

                                                                servo_90();
                                        delay_ms(10);

                                        uart0_tx_string("\r\n temp=");
                                        uart0_float(temp);
                                        uart0_tx_string("\r\n");

                                        uart0_tx_string("distance:");
                                        uart0_float(distance);
                                        uart0_tx_string("\r\n");


                                        uart0_tx_string("water level is :");
                                        uart0_integer(water);
                                        uart0_tx_string("\r\n");
                                        delay_ms(500);
                                        break;
                                }
                                }
                                }

                                else if(water>=20&&water<50)
                                {
                                        uart0_tx_string("water level is medium\r\n");
                                        IOSET0|=GREEN_LED|RED_LED;
                                        IOCLR0|=YELLOW_LED;
                                        }
                                        else if(water>=50)
                                        {
                                        uart0_tx_string("\r\n high water level\r\n");
                                        uart0_tx_string("turn off the motor\r\n");
                                        IOSET0|=GREEN_LED|YELLOW_LED;
                                        IOCLR0|=RED_LED;
                                        while(1)
                                        {
                                        if(sw2==0){
                                        while(sw2==0);

                                        servo_0();
                                        uart0_tx_string("\r\nPUMP STATUS : OFF\r\n");
                                        uart0_tx_string("\r\n RELAY STATUS:OFF\r\n");
                                        uart0_tx_string("\r\n VALUE STATUS :CLOSE\r\n");

                                        delay_ms(100);

                                        uart0_tx_string("\r\n temp=");
                                        uart0_float(temp);
                                        uart0_tx_string("\r\n");

                                        uart0_tx_string("water level is :");
                                        uart0_integer(water);
                                        uart0_tx_string("\r\n");
                                        delay_sec(500);

                                        uart0_tx_string("distance:");
                                        uart0_float(distance);
                                        uart0_tx_string("\r\n");

                                        break;
                                        }
                                        }
                                        }
                                        }
                                        else
                                        {
                                        uart0_tx_string("\r\n automtic mode\r\n");
                                        if(water<20)
                                        {
                                        uart0_tx_string("\r\nLOW WATER LEVEL\r\n");
                                        IOSET0|=RED_LED|YELLOW_LED;
                                        IOCLR0|=GREEN_LED;

                                        servo_90();
                                        uart0_tx_string("\r\nPUMP STATUS : ON\r\n");
                                        uart0_tx_string("\r\n RELAY STATUS:ON\r\n");
                                        uart0_tx_string("\r\n VALUE STATUS :OPEN\r\n");


                                        uart0_tx_string("\r\n temp=");
                                        uart0_float(temp);
                                        uart0_tx_string("\r\n");

                                        uart0_tx_string("distance:");
                                        uart0_float(distance);
                                        uart0_tx_string("\r\n");


                                        uart0_tx_string("water level is :");
                                        uart0_integer(water);
                                        uart0_tx_string("\r\n");
                                        delay_ms(500);
                                        }

                                        else if(water>=20&&water<50)
                                        {
                                        uart0_tx_string("\r\n MEDIUM WATER LEVEL\r\n");
                                        IOSET0|=GREEN_LED|RED_LED;
                                        IOCLR0|=YELLOW_LED;
                                        }

                                        else if(water>=50)
                                        {
                                        uart0_tx_string("\r\n high water level\r\n");
                                        uart0_tx_string("turn off the motor\r\n");
                                        IOSET0|=GREEN_LED|YELLOW_LED;
                                        IOCLR0|=RED_LED;

                                        servo_0();
                                        uart0_tx_string("\r\nPUMP STATUS : OFF\r\n");
                                        uart0_tx_string("\r\n RELAY STATUS:OFF\r\n");
                                        uart0_tx_string("\r\n VALUE STATUS :CLOSE\r\n");


                                        uart0_tx_string("\r\n temp=");
                                        uart0_float(temp);
                                        uart0_tx_string("\r\n");

                                        uart0_tx_string("distance:");
                                        uart0_float(distance);
                                        uart0_tx_string("\r\n");


                                        uart0_tx_string("water level is :");
                                        uart0_integer(water);
                                        uart0_tx_string("\r\n");
                                        delay_ms(500);
                                        }
                                        }
                                        uart0_tx_string("rtc date:");
                                                day=i2c_receive(0xD1,0x04);//read date;
                                                month=i2c_receive(0xD1,0x05);//read month;
                                                year=i2c_receive(0xD1,0x06);//read year;


                                                uart0_tx((day/0x10)+48);
                                                uart0_tx((day%0x10)+48);
                                                uart0_tx('/');
                                                uart0_tx((month/0x10)+48);
                                                uart0_tx((month%0x10)+48);
                                                uart0_tx('/');
                                                uart0_tx((year/0x10)+48);
                                                uart0_tx((year%0x10)+48);
                                                uart0_tx_string("\r\n");


                                                uart0_tx_string("rtc time:");
                                            h=i2c_receive(0xD1,0x02);//read hrs
                                                m=i2c_receive(0xD1,0x01);//read mins
                                                s=i2c_receive(0xD1,0x00);//read secs

                                                clean_h=h & 0x1f;// first 5 bits are used other 3 are masked
                                                uart0_tx((clean_h/0x10)+48);
                                                uart0_tx((clean_h%0x10)+48);
                                                uart0_tx(':');
                                                uart0_tx((m/0x10)+48);
                                                uart0_tx((m%0x10)+48);
                                                uart0_tx(':');
                                                uart0_tx((s/0x10)+48);
                                                uart0_tx((s%0x10)+48);
                                                uart0_tx_string("\r\n");
                                                delay_sec(10);

                                                epprom(temp);




                                        }
                                }
}
