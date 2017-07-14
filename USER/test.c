#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "LED.h" 
 

int main(void)
{								  
	u16 t;
	u16 len;	
	u16 times=0;    
	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,115200); 	//串口初始化为115200
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口 
 	while(1)
	{
		Led_Flash(100);
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3FFF;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);//等待发送结束
			}
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
			delay_ms(10);   
		}
	}		 
}

