#include "pwm.h"

//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB1ENR|=1<<1; 	//TIM3ʱ��ʹ��    
	RCC->APB2ENR|=1<<3;    	//ʹ��PORTBʱ��	
	GPIOB->CRL&=0XFF0FFFFF;	//PB5���
	GPIOB->CRL|=0X00B00000;	//���ù������ 	  	 
	   
	RCC->APB2ENR|=1<<0;     //��������ʱ��	   
	AFIO->MAPR&=0XFFFFF3FF; //���MAPR��[11:10]
	AFIO->MAPR|=1<<11;      //������ӳ��,TIM3_CH2->PB5

	TIM3->ARR=arr;			//�趨�������Զ���װֵ 
	TIM3->PSC=psc;			//Ԥ��Ƶ������Ƶ
	
	TIM3->CCMR1|=7<<12;  	//CH2 PWM2ģʽ		 
	TIM3->CCMR1|=1<<11; 	//CH2Ԥװ��ʹ��	   
	TIM3->CCER|=1<<4;   	//OC2 ���ʹ��	   
	TIM3->CR1=0x0080;   	//ARPEʹ�� 
	TIM3->CR1|=0x01;    	//ʹ�ܶ�ʱ��3 											  
}  	
