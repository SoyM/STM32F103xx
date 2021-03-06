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
u8 temp, humi, humi_dec, temp_dec;
u8 R=0x00,G=0x00,B=0x00;
float Max=0,Min=0;
float Rhsv=0,Ghsv=0,Bhsv=0;
float H=0,S=0,V=0;
float adc2;
u16 adc1;
int main(void)
{								  
	Stm32_Clock_Init(9);
	delay_init(72);	 		
	JTAG_Set(JTAG_SWD_DISABLE); 
	JTAG_Set(SWD_ENABLE);
	LED_Init();
	KEY_Init();
	//OLED_Init();  
	uart_init(72,115200);
	printf("begin");
	//uart2_init(36,9600);
	//MiniBalance_PWM_Init(7199,0);
	//Encoder_Init_TIM2();           
	//Encoder_Init_TIM3();           
	//IIC_Init();
	//MPU6050_initialize();
	//DMP_Init();
	//Flash_Read(); 
	//EXTI_Init();  
	//DHT11_init();
	//HC_SR04_init();
	//TIM3_Cap_Init(0XFFFF,71);
	//-tcs3200_init();
	//-whitebalance();
	//LED=0;
	//InitRc522();
	//NRF24L01_Init();
	//NRF24L01_FindMyself(); 
	//Qingxie_Init();
	//Adc_Init();
	Dac1_Init();
	Dac1_Set_Vol(3300);
 	while(1)
	{/*
	if(Flash_Send==1)          //写入PID参数到Flash,由app控制该指令
		{
			Flash_Write();	
			Flash_Send=0;	
		}	
		if(Flag_Show==0){
			APP_Show();	
			oled_show();             
		}
		else{
			DataScope();
		}
		delay_flag=1;	
		delay_50=0;
		while(delay_flag);	     //通过MPU6050的INT中断实现的50ms精准延时 */
		//uart_receive(); 
		//HC_SR04_run();
		//Read_Distane();
		//printf("%d\n",Distance);
		//delay_ms(500);
		//LED=~LED;
		//if(DHT11_Read_Data(&humi,&temp,&humi_dec,&temp_dec)){	
		//printf("temp:%d.%d,humi:%d.%d\n",temp,temp_dec,humi,humi_dec);
		//}
		///en=0;
		///R = tcs3200_RED();
		///G = tcs3200_GREEN();	//取RGB值
		///B = tcs3200_BLUE();	 
		///en=1;
		///printf("R-%d,G-%d,B-%d\n",R,G,B);
		//NRF24L01();
		//Qingxie_check();
		//adc1=Get_Adc(4);
		//printf("%d\n",adc1);
		//adc2=(float)adc1*(3.3/4096);
		//printf("V=%f\n",adc2);
		LED=~LED;
		DAC->DHR12R1=100;
		adc1=GPIOA->CRL;
		printf("%d",adc1);
		delay_ms(1000);
	}		 
}

