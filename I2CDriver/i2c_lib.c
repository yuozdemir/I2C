#ifndef I2CLIB_H_
#define I2CLIB_H_

#define SDA                  PIN_F4              //SDA ve SCL pinlerini belirle
#define SCL                  PIN_F5
#define DELAY                delay_us(5);        //Haberleþme hýzýna göre gecikme süresi belirle

int i2c_start(void)                                  //Baþlama bitini gönderecek olan fonksiyon
{
   output_high(SDA);
   output_high(SCL);
   DELAY
   
   if(input_state(SDA) == 0) return 0;           //Hattýn durumunu sorgular
   
   output_low(SDA);
   DELAY
   output_low(SCL);
}

void i2c_stop(void)                                  //Durdurma bitini gönderecek olan fonksiyon
{
   output_low(SDA);
   output_high(SCL);
   DELAY
   while(input_state(SCL) == 0);                 //SCL pininin HIGH duruma geçmesini bekler
   output_high(SDA);
   DELAY
}

int i2c_write(unsigned int8 data)                    //DAC register veya eeprom a veri yazma fonksiyonu
{  
   int1 ret;                                     //ACK ve NACK bitlerini döndürmesi için deðiþken
   
   for(int i=0; i<8; i++)                        //Veriyi bit bit yollayacak olan for döngüsü
   {     
      if (data & 0x01) output_high(SDA);         //Verinin ilk bitini sorgular
      else output_low(SDA);
      
      DELAY
      output_high(SCL);
      DELAY
      
      data = data >> 1;                          //Veriyi bir bit saða ötele
      
      output_low(SCL);
   }
   
   output_high(SDA);
   DELAY
   output_high(SCL);
   DELAY
   
   ret = input_state(SDA);                       //ACK veya NACK bitini ret deðiþkenine yaz
   
   output_low(SCL);
   DELAY
   
   return ret;                                   //ACK bitini döndür
}

#endif                       //I2C.lib
