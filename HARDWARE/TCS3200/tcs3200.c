#include "tcs3200.h"
#include "exti.h"


u8 Rgena,Ggena,Bgena;
u16 Ramount,Gamount,Bamount;
u16 amount;

void tcs3200_init(void)
{
	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��	   
	GPIOB->CRH&=0xFF00FFFF;
	GPIOB->CRH|=0x00330000;//PB12,PB13�������
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
*		  ��ƽ��
*
*******************************************/
void whitebalance(void)
{
	S2=0;S3=0;//en=0;//��ɫͨ��
	amount=0;			 //��ʼ����
	delay_ms(10);
	Rgena = amount;   //�����ɫ���� 
	amount=0;
//----------------------------------
	S2=1;S3=1;//��ɫͨ��
	amount=0;
	delay_ms(10);
	Ggena = amount;	 //�����ɫ����
	amount=0;
//----------------------------------
	S2=0;S3=1;//��ɫͨ��
	amount=0;
	delay_ms(10);
	Bgena = amount;	  //�����ɫ����
	amount=0;
	//S2=1;S3=0;//�ر�ͨ��  
	//en=1;	
}  

u16 tcs3200_RED(void)
{
	S2=0;S3=0;
	amount=0;
	delay_ms(10);
	printf("c-%d\n",amount);
	Ramount=(u32) amount*255/Rgena;	 //ȡRֵ
	if(Ramount>255) Ramount = 255;
	return Ramount;
//	amount=0;
}

u16 tcs3200_GREEN(void)
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10);
	Gamount=(u32) amount*255/Ggena;	//ȡGֵ
	if(Gamount>255) Gamount = 255;
	return Gamount;
//	amount=0;
}

u16 tcs3200_BLUE(void)
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10);
	Bamount=(u32) amount*255/Bgena;//ȥBֵ
	if(Bamount>255) Bamount = 255;
	return Bamount;
//	amount=0;
}

void EXTI0_IRQHandler(void)
{
	amount++;
	printf("c-%d\n",amount);
	EXTI->PR=1<<4;  //���LINE0�ϵ��жϱ�־λ
}

