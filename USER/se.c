#include "sys.h" 	
#include "delay.h"	
#include "usart.h"

//LED��ʼ��
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

//������ʼ��
void KEY_Init(void)
{
	RCC->APB2ENR |= 1 << 2;     //ʹ��PORTAʱ��
	RCC->APB2ENR |= 1 << 6;     //ʹ��PORTEʱ��
	GPIOA->CRL &= 0XFFFFFFF0;	//PA0���ó����룬Ĭ������	  
	GPIOA->CRL |= 0X00000008;

	GPIOE->CRL &= 0XFFF000FF;	//PE2~4���ó����� 
	GPIOE->CRL |= 0X00088800;
	GPIOE->ODR |= 7 << 2;	   	//PE2~4����
}

int main(void)
{				  
	Stm32_Clock_Init(9);//ϵͳʱ������
	uart_init(72,115200);
	delay_init(72);	  	//��ʱ��ʼ��
	LED_Init();
	KEY_Init;
	while(1)
	{
		if (USART_RX_STA & 0x8000)
		{
			len = USART_RX_STA & 0x3FFF;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n\r\n");
			for (t = 0; t<len; t++)
			{
				USART1->DR = USART_RX_BUF[t];
				while ((USART1->SR & 0X40) == 0);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA = 0;
		}
		else
		{
			times++;
			if (times % 200 == 0)printf("����������,�Իس�������\r\n");
			delay_ms(10);
		}
	}	 
}


