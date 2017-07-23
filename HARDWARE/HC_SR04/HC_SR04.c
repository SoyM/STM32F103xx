//���������ģ��,PB0����-echo��PB1���-trig��
#include "HC_SR04.h"

void HC_SR04_init(void){
	RCC->APB2ENR|=1<<3;
	GPIOB->CRH&=0XFF00FFFF;
	GPIOB->CRH|=0X00380000;
	//GPIOB->ODR|=1<<12;
}

/**************************************************************************
�������ܣ����������ջز�����
��ڲ�������
����  ֵ����
**************************************************************************/
u16 TIM3CH3_CAPTURE_STA,TIM3CH3_CAPTURE_VAL;
void Read_Distane(void)
{   
	 PBout(1)=1;
	 delay_us(15);  
	 PBout(1)=0;
		printf("R1\n");
			if(TIM3CH3_CAPTURE_STA&0X80)//�ɹ�������һ�θߵ�ƽ
		{
			Distance=TIM3CH3_CAPTURE_STA&0X3F;
			Distance*=65536;					        //���ʱ���ܺ�
			Distance+=TIM3CH3_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
			//printf("%d \r\n",TIM3CH3_CAPTURE_VAL);
			Distance=Distance*170/1000;
			//printf("%d \r\n",Distance);
			TIM3CH3_CAPTURE_STA=0;			//������һ�β���
		}				
}
/**************************************************************************
�������ܣ��������ز������ȡ�ж�
**************************************************************************/
void TIM3_IRQHandler(void)
{ 		    		  			    
	u16 tsr;
	tsr=TIM3->SR;
	if((TIM3CH3_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{
			if(tsr&0X01)//���
			{	   				
					if(TIM3CH3_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
					{
						if((TIM3CH3_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
						{
							TIM3CH3_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
							TIM3CH3_CAPTURE_VAL=0XFFFF;
						}
						else 
							TIM3CH3_CAPTURE_STA++;
					}	 
			}
			if(tsr&0x08)//����3���������¼�
			{	
					if(TIM3CH3_CAPTURE_STA&0X40)		//����һ���½��� 		
					{	  
							TIM3CH3_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
							TIM3CH3_CAPTURE_VAL=TIM3->CCR3;	//��ȡ��ǰ�Ĳ���ֵ.
							TIM3->CCER&=~(1<<9);			//CC1P=0 ����Ϊ�����ز���
					}else  								//��δ��ʼ,��һ�β���������
				  {
							TIM3CH3_CAPTURE_STA=0;			//���
							TIM3CH3_CAPTURE_VAL=0;
							TIM3CH3_CAPTURE_STA|=0X40;		//��ǲ�����������
							TIM3->CNT=0;					//���������
							TIM3->CCER|=1<<9; 				//CC1P=1 ����Ϊ�½��ز���
					}		    
			}			     	    					   
	}
	TIM3->SR=0;//����жϱ�־λ 	     
}

