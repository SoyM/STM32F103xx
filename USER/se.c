#include "sys.h" 	
#include "delay.h"	
#include "led.h"

#define LED0 PBout(5)
#define LED1 PEout(5)

//初始化与LED连接的硬件接口
void LED_Init(void)
{
	RCC->APB2ENR |= 1 << 3;    //使能PORTB时钟	   	 
	RCC->APB2ENR |= 1 << 6;    //使能PORTE时钟	

	GPIOB->CRL &= 0XFF0FFFFF;
	GPIOB->CRL |= 0X00300000;//PB.5 推挽输出   	 
	GPIOB->ODR |= 1 << 5;      //PB.5 输出高

	GPIOE->CRL &= 0XFF0FFFFF;
	GPIOE->CRL |= 0X00300000;//PE.5推挽输出
	GPIOE->ODR |= 1 << 5;      //PE.5输出高 
}

int main(void)
{				  
	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);	  	//延时初始化
	LED_Init();		  	
	while(1)
	{
		LED0=0;
		LED1=1;
		delay_ms(300);
		LED0=1;
		LED1=0;
		delay_ms(300);
	}	 
}


