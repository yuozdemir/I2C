#ifndef I2CLIB_H_
#define I2CLIB_H_

#define SDA                  PIN_F4              //SDA ve SCL pinlerini belirle
#define SCL                  PIN_F5
#define DELAY                delay_us(5);        //Haberle�me h�z�na g�re gecikme s�resi belirle

int i2c_start(void)                                  //Ba�lama bitini g�nderecek olan fonksiyon
{
   output_high(SDA);
   output_high(SCL);
   DELAY
   
   if(input_state(SDA) == 0) return 0;           //Hatt�n durumunu sorgular
   
   output_low(SDA);
   DELAY
   output_low(SCL);
}

void i2c_stop(void)                                  //Durdurma bitini g�nderecek olan fonksiyon
{
   output_low(SDA);
   output_high(SCL);
   DELAY
   while(input_state(SCL) == 0);                 //SCL pininin HIGH duruma ge�mesini bekler
   output_high(SDA);
   DELAY
}

int i2c_write(unsigned int8 data)                    //DAC register veya eeprom a veri yazma fonksiyonu
{  
   int1 ret;                                     //ACK ve NACK bitlerini d�nd�rmesi i�in de�i�ken
   
   for(int i=0; i<8; i++)                        //Veriyi bit bit yollayacak olan for d�ng�s�
   {     
      if (data & 0x01) output_high(SDA);         //Verinin ilk bitini sorgular
      else output_low(SDA);
      
      DELAY
      output_high(SCL);
      DELAY
      
      data = data >> 1;                          //Veriyi bir bit sa�a �tele
      
      output_low(SCL);
   }
   
   output_high(SDA);
   DELAY
   output_high(SCL);
   DELAY
   
   ret = input_state(SDA);                       //ACK veya NACK bitini ret de�i�kenine yaz
   
   output_low(SCL);
   DELAY
   
   return ret;                                   //ACK bitini d�nd�r
}

#endif                       //I2C.lib
