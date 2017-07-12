#include "sys.h" 	
#include "delay.h"	
#include "led.h"

//LED初始化
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

//按键初始化
void KEY_Init(void)
{
	RCC->APB2ENR |= 1 << 2;     //使能PORTA时钟
	RCC->APB2ENR |= 1 << 6;     //使能PORTE时钟
	GPIOA->CRL &= 0XFFFFFFF0;	//PA0设置成输入，默认下拉	  
	GPIOA->CRL |= 0X00000008;

	GPIOE->CRL &= 0XFFF000FF;	//PE2~4设置成输入 
	GPIOE->CRL |= 0X00088800;
	GPIOE->ODR |= 7 << 2;	   	//PE2~4上拉
}

int main(void)
{				  
	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);	  	//延时初始化
	LED_Init();
	KEY_Init;
	while(1)
	{
	}	 
}


