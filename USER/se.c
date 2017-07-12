#include "sys.h" 	
#include "delay.h"	
#include "led.h"

#define LED0 PBout(5)
#define LED1 PEout(5)

//��ʼ����LED���ӵ�Ӳ���ӿ�
void LED_Init(void)
{
	RCC->APB2ENR |= 1 << 3;    //ʹ��PORTBʱ��	   	 
	RCC->APB2ENR |= 1 << 6;    //ʹ��PORTEʱ��	

	GPIOB->CRL &= 0XFF0FFFFF;
	GPIOB->CRL |= 0X00300000;//PB.5 �������   	 
	GPIOB->ODR |= 1 << 5;      //PB.5 �����

	GPIOE->CRL &= 0XFF0FFFFF;
	GPIOE->CRL |= 0X00300000;//PE.5�������
	GPIOE->ODR |= 1 << 5;      //PE.5����� 
}

int main(void)
{				  
	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);	  	//��ʱ��ʼ��
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


