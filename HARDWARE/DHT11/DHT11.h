#ifndef _DTH11_H
#define _DTH11_H
#include "stm32f10x.h"
#include "sys.h"

#define DHT11_IO_IN()  {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=8<<16;}
#define DHT11_IO_OUT() {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=3<<16;}

#define DHT11_DQ_OUT PBout(12)
#define DHT11_DQ_IN PBin(12)

void DHT11_Rst(void);
char DHT11_Check(void);
void DHT11_Read_Byte(void);
char DHT11_Read_Data(u8 *humi,u8 *temp,u8 *humi_dec,u8 *temp_dec);  
char DHT11_init(void);
#endif
