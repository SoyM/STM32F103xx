#include "led.h"
//��ʼ�� PA8 Ϊ�����.��ʹ��PORTA�ڵ�ʱ��
void LED_Init(void)
{
RCC->APB2ENR|=1<<2; //ʹ�� PORTA ʱ��  
GPIOA->CRH&=0XFFFFFFF0;
GPIOA->CRH|=0X00000003;//PA8 �������
GPIOA->ODR|=1<<8; //PA8 �����
}

/**************************************************************************
�������ܣ�LED��˸
��ڲ�������˸Ƶ�� 
����  ֵ����
**************************************************************************/
void Led_Flash(u16 time)
{
	  static int temp;
		if(++temp==time)	LED=~LED,temp=0;
}