
#include "usart2.h"


/**************************************************************************
�������ܣ�����2��ʼ��
��ڲ�����pclk2:PCLK2 ʱ��Ƶ��(Mhz)    bound:������
����  ֵ����
**************************************************************************/
void uart2_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				                 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
  mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB1ENR|=1<<17;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRL&=0XFFFF00FF; 
	GPIOA->CRL|=0X00008B00;//IO״̬����
	GPIOA->ODR|=1<<2;	  
	RCC->APB1RSTR|=1<<17;   //��λ����1
	RCC->APB1RSTR&=~(1<<17);//ֹͣ��λ	   	   
	//����������
 	USART2->BRR=mantissa; // ����������	 
	USART2->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//ʹ�ܽ����ж�
	USART2->CR1|=1<<8;    //PE�ж�ʹ��
	USART2->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(0,1,USART2_IRQn,2);//��2
}

/**************************************************************************
�������ܣ�����2�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/
void USART2_IRQHandler(void)
{	
	if(USART2->SR&(1<<5))//���յ�����
	{	  
    int Usart3_Receive;//����������ر���
	  static u8 Flag_PID,i,j,Receive[50];
		static u16 Data;
   	Usart3_Receive=USART2->DR; 
		if(Usart3_Receive==0x7B) Flag_PID=1;  //ָ����ʼλ
		if(Usart3_Receive==0x7D) Flag_PID=2;  //ָ��ֹͣλ
		 if(Flag_PID==1)                      //��¼����
		 {
			Receive[i]=Usart3_Receive;
			i++;
		 }
		 if(Flag_PID==2)   //ִ��
		 {
			     if(Receive[3]==0x50) 	       PID_Send=1;     //��ȡ�豸����
					 else  if(Receive[3]==0x57) 	 Flash_Send=1;   //���籣�����
					 else  if(Receive[1]!=0x23)                    //����PID����
					 {								
						for(j=i;j>=4;j--)
						{
							Data+=(Receive[j-1]-0x30)*pow(10,i-j);
						}
						switch(Receive[1])
						 {
							 case 0x30:  PA=(float)Data;break;
							 case 0x31:  PB=(float)Data;break;
							 case 0x32:  PC=(float)Data;break;
							 case 0x33:  PD=(float)Data;break;
							 case 0x34:  break;
							 case 0x35:  break;
							 case 0x36:  break;
							 case 0x37:  break;
							 case 0x38:  break;
						 }
					 }				 
					 Flag_PID=0;   //��ر�־λ����
					 i=0;
					 j=0;
					 Data=0;
				//	 memset(Receive, 0, sizeof(u8)*50);
		 } 
	}  											 
} 


