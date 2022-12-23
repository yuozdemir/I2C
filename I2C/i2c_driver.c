#include"setup.h"                                //SETUP
#include"i2c_lib.c"                              //I2C KUTUPHANESI

#define dac_address          0x23                //DAC ADDRESS
#define SS1_A0               PIN_B11             //DAC1 A0
#define SS2_A0               PIN_B10             //DAC2 A0

void main()
{  
   unsigned int8 data = 0xFF;                    //Veri
   int1 ret;                                     //ACK sorgulama için deðiþken
   
   output_bit(SS1_A0, 1);                        //DAC A0 pini adres ayarý
   output_bit(SS2_A0, 0);
   
   output_high(SDA);                             //Baþlangýçta SDA ve SCL çýkýþlarýný HIGH duruma getir
   output_high(SCL);
   
   i2c_start();                                      //Baþlangýç bitini yolla
   
   ret = i2c_write(dac_address);                     //Adresi yolla
   if (!ret) stop();                             //ACK bitini sorgula
   
   i2c_write(0xF0);                                  //Fast mod setup settings
   i2c_write(data);                                  //Veriyi yolla
   
   i2c_stop();                                       //Stop bitini yolla
   
   while(TRUE);
}
