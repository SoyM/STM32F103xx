#include "timer.h"
/**************************************************************************
函数功能：定时器3通道3输入捕获初始化
入口参数：入口参数：arr：自动重装值  psc：时钟预分频数 
返回  值：无
**************************************************************************/
void TIM3_Cap_Init(u16 arr,u16 psc)	
{	 
	RCC->APB1ENR|=1<<1;     //TIM3时钟使能     
	
  TIM3->ARR=arr;  		//设定计数器自动重装值   
	TIM3->PSC=psc;  		//预分频器 
	TIM3->CCMR2|=1<<0;	//选择输入端 
 	TIM3->CCMR2|=0<<4; 	// 配置输入滤波器 不滤波
 	TIM3->CCMR2|=0<<2; 	//配置输入分频,不分频 

	TIM3->CCER|=0<<9; 	//上升沿捕获
	TIM3->CCER|=1<<8; 	//允许捕获计数器的值到捕获寄存器中

	TIM3->DIER|=1<<3;   //允许捕获中断				
	TIM3->DIER|=1<<0;   //允许更新中断	
	TIM3->CR1|=0x01;    //使能定时器3
	MY_NVIC_Init(1,3,TIM3_IRQn,1);
}
