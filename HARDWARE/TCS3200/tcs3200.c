#include "tcs3200.h"
#include "exti.h"


u8 Rgena,Ggena,Bgena;
u16 Ramount,Gamount,Bamount;
u16 amount;

void tcs3200_init(void)
{
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟	   
	GPIOB->CRH&=0xFF00FFFF;
	GPIOB->CRH|=0x00330000;//PB12,PB13推挽输出
	printf("T1");
	//GPIOB->CRL&=0xFFFFFF0F;
	printf("T1");
	//GPIOB->CRL|=0X00000030;
	printf("T1");
	GPIOB->ODR|=1<<12;
	GPIOB->ODR|=1<<13;
	GPIOB->ODR|=0<<1;
	printf("T1");
}
/*******************************************
*
*		  白平衡
*
*******************************************/
void whitebalance(void)
{
	S2=0;S3=0;//en=0;//红色通道
	amount=0;			 //开始计数
	delay_ms(10);
	Rgena = amount;   //求出红色因子 
	amount=0;
//----------------------------------
	S2=1;S3=1;//绿色通道
	amount=0;
	delay_ms(10);
	Ggena = amount;	 //求出绿色因子
	amount=0;
//----------------------------------
	S2=0;S3=1;//蓝色通道
	amount=0;
	delay_ms(10);
	Bgena = amount;	  //求出蓝色因子
	amount=0;
	//S2=1;S3=0;//关闭通道  
	//en=1;	
}  

u16 tcs3200_RED(void)
{
	S2=0;S3=0;
	amount=0;
	delay_ms(10);
	printf("c-%d\n",amount);
	Ramount=(u32) amount*255/Rgena;	 //取R值
	if(Ramount>255) Ramount = 255;
	return Ramount;
//	amount=0;
}

u16 tcs3200_GREEN(void)
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10);
	Gamount=(u32) amount*255/Ggena;	//取G值
	if(Gamount>255) Gamount = 255;
	return Gamount;
//	amount=0;
}

u16 tcs3200_BLUE(void)
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10);
	Bamount=(u32) amount*255/Bgena;//去B值
	if(Bamount>255) Bamount = 255;
	return Bamount;
//	amount=0;
}

void EXTI0_IRQHandler(void)
{
	amount++;
	printf("c-%d\n",amount);
	EXTI->PR=1<<4;  //清除LINE0上的中断标志位
}

