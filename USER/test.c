#include "sys.h"
u8 Way_Angle=1;                             //获取角度的算法，1：四元数 
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //蓝牙遥控相关的变量
u8 Flag_Stop=1,Flag_Show=1;                 //停止标志位和 显示标志位 默认停止 显示打开
int Encoder_Left,Encoder_Right;             //左右编码器的脉冲计数
int Moto1,Moto2;                            //电机PWM变量 应是Motor的 向Moto致敬	
int Temperature;                            //显示温度
int Voltage;                                //电池电压采样相关的变量
float Angle_Balance,Gyro_Balance,Gyro_Turn; //平衡倾角 平衡陀螺仪 转向陀螺仪
float Show_Data_Mb;                         //全局显示变量，用于显示需要查看的数据
u32 Distance;                               //超声波测距
u8 delay_50,delay_flag,Bi_zhang=0,PID_Send,Flash_Send;   //默认情况下
float Acceleration_Z;                       //Z轴加速度计  
float PA=100,PB=500,PC=888,PD=6813;//PID参数
u16 PID_Parameter[10],Flash_Parameter[10];  //Flash相关数组	

int main(void)
{								  
//	u16 t,len,times;
	Stm32_Clock_Init(9);
	delay_init(72);	 	
	uart_init(72,115200); 	
	JTAG_Set(JTAG_SWD_DISABLE); 
	JTAG_Set(SWD_ENABLE);
	LED_Init();
	KEY_Init();
	Encoder_Init_TIM2();           
	Encoder_Init_TIM3();           
	IIC_Init();
	MPU6050_initialize();
	DMP_Init();
	EXTI_Init();
	LED=0;
 	while(1)
	{
    //Led_Flash(100);
//		if(USART_RX_STA&0x8000)
//		{					   
//			len=USART_RX_STA&0x3FFF;//得到此次接收到的数据长度
//			printf("\r\n您发送的消息为:\r\n\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART1->DR=USART_RX_BUF[t];
//				while((USART1->SR&0X40)==0);//等待发送结束
//			}
//			printf("\r\n\r\n");//插入换行
//			USART_RX_STA=0;
//		}else
//		{
//			times++;
//			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
//			delay_ms(10);   
//		}
		DataScope();
		delay_flag=1;	
		delay_50=0;
		while(delay_flag);	     //通过MPU6050的INT中断实现的50ms精准延�

	}		 
}

