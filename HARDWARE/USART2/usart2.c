
#include "usart2.h"


/**************************************************************************
函数功能：串口2初始化
入口参数：pclk2:PCLK2 时钟频率(Mhz)    bound:波特率
返回  值：无
**************************************************************************/
void uart2_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				                 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
  mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
	RCC->APB1ENR|=1<<17;  //使能串口时钟 
	GPIOA->CRL&=0XFFFF00FF; 
	GPIOA->CRL|=0X00008B00;//IO状态设置
	GPIOA->ODR|=1<<2;	  
	RCC->APB1RSTR|=1<<17;   //复位串口1
	RCC->APB1RSTR&=~(1<<17);//停止复位	   	   
	//波特率设置
 	USART2->BRR=mantissa; // 波特率设置	 
	USART2->CR1|=0X200C;  //1位停止,无校验位.
	//使能接收中断
	USART2->CR1|=1<<8;    //PE中断使能
	USART2->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	MY_NVIC_Init(0,1,USART2_IRQn,2);//组2
}

/**************************************************************************
函数功能：串口2接收中断
入口参数：无
返回  值：无
**************************************************************************/
void USART2_IRQHandler(void)
{	
	if(USART2->SR&(1<<5))//接收到数据
	{	  
    int Usart3_Receive;//蓝牙接收相关变量
	  static u8 Flag_PID,i,j,Receive[50];
		static u16 Data;
   	Usart3_Receive=USART2->DR; 
		if(Usart3_Receive==0x7B) Flag_PID=1;  //指令起始位
		if(Usart3_Receive==0x7D) Flag_PID=2;  //指令停止位
		 if(Flag_PID==1)                      //记录参数
		 {
			Receive[i]=Usart3_Receive;
			i++;
		 }
		 if(Flag_PID==2)   //执行
		 {
			     if(Receive[3]==0x50) 	       PID_Send=1;     //获取设备参数
					 else  if(Receive[3]==0x57) 	 Flash_Send=1;   //掉电保存参数
					 else  if(Receive[1]!=0x23)                    //更新PID参数
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
					 Flag_PID=0;   //相关标志位清零
					 i=0;
					 j=0;
					 Data=0;
				//	 memset(Receive, 0, sizeof(u8)*50);
		 } 
	}  											 
} 


