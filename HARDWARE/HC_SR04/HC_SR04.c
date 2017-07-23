//超声波测距模块,PB0输入-echo，PB1输出-trig。
#include "HC_SR04.h"

void HC_SR04_init(void){
	RCC->APB2ENR|=1<<3;
	GPIOB->CRH&=0XFF00FFFF;
	GPIOB->CRH|=0X00380000;
	//GPIOB->ODR|=1<<12;
}

/**************************************************************************
函数功能：超声波接收回波函数
入口参数：无
返回  值：无
**************************************************************************/
u16 TIM3CH3_CAPTURE_STA,TIM3CH3_CAPTURE_VAL;
void Read_Distane(void)
{   
	 PBout(1)=1;
	 delay_us(15);  
	 PBout(1)=0;
		printf("R1\n");
			if(TIM3CH3_CAPTURE_STA&0X80)//成功捕获到了一次高电平
		{
			Distance=TIM3CH3_CAPTURE_STA&0X3F;
			Distance*=65536;					        //溢出时间总和
			Distance+=TIM3CH3_CAPTURE_VAL;		//得到总的高电平时间
			//printf("%d \r\n",TIM3CH3_CAPTURE_VAL);
			Distance=Distance*170/1000;
			//printf("%d \r\n",Distance);
			TIM3CH3_CAPTURE_STA=0;			//开启下一次捕获
		}				
}
/**************************************************************************
函数功能：超声波回波脉宽读取中断
**************************************************************************/
void TIM3_IRQHandler(void)
{ 		    		  			    
	u16 tsr;
	tsr=TIM3->SR;
	if((TIM3CH3_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{
			if(tsr&0X01)//溢出
			{	   				
					if(TIM3CH3_CAPTURE_STA&0X40)//已经捕获到高电平了
					{
						if((TIM3CH3_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
						{
							TIM3CH3_CAPTURE_STA|=0X80;//标记成功捕获了一次
							TIM3CH3_CAPTURE_VAL=0XFFFF;
						}
						else 
							TIM3CH3_CAPTURE_STA++;
					}	 
			}
			if(tsr&0x08)//捕获3发生捕获事件
			{	
					if(TIM3CH3_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
					{	  
							TIM3CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
							TIM3CH3_CAPTURE_VAL=TIM3->CCR3;	//获取当前的捕获值.
							TIM3->CCER&=~(1<<9);			//CC1P=0 设置为上升沿捕获
					}else  								//还未开始,第一次捕获上升沿
				  {
							TIM3CH3_CAPTURE_STA=0;			//清空
							TIM3CH3_CAPTURE_VAL=0;
							TIM3CH3_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
							TIM3->CNT=0;					//计数器清空
							TIM3->CCER|=1<<9; 				//CC1P=1 设置为下降沿捕获
					}		    
			}			     	    					   
	}
	TIM3->SR=0;//清除中断标志位 	     
}

