#include "sys.h"
u8 Way_Angle=1;                             //»ñÈ¡½Ç¶ÈµÄËã·¨£¬1£ºËÄÔªÊı 
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //À¶ÑÀÒ£¿ØÏà¹ØµÄ±äÁ¿
u8 Flag_Stop=1,Flag_Show=1;                 //Í£Ö¹±êÖ¾Î»ºÍ ÏÔÊ¾±êÖ¾Î» Ä¬ÈÏÍ£Ö¹ ÏÔÊ¾´ò¿ª
int Encoder_Left,Encoder_Right;             //×óÓÒ±àÂëÆ÷µÄÂö³å¼ÆÊı
int Moto1,Moto2;                            //µç»úPWM±äÁ¿ Ó¦ÊÇMotorµÄ ÏòMotoÖÂ¾´	
int Temperature;                            //ÏÔÊ¾ÎÂ¶È
int Voltage;                                //µç³ØµçÑ¹²ÉÑùÏà¹ØµÄ±äÁ¿
float Angle_Balance,Gyro_Balance,Gyro_Turn; //Æ½ºâÇã½Ç Æ½ºâÍÓÂİÒÇ ×ªÏòÍÓÂİÒÇ
float Show_Data_Mb;                         //È«¾ÖÏÔÊ¾±äÁ¿£¬ÓÃÓÚÏÔÊ¾ĞèÒª²é¿´µÄÊı¾İ
u32 Distance;                               //³¬Éù²¨²â¾à
u8 delay_50,delay_flag,Bi_zhang=0,PID_Send,Flash_Send;   //Ä¬ÈÏÇé¿öÏÂ
float Acceleration_Z;                       //ZÖá¼ÓËÙ¶È¼Æ  
float PA=100,PB=500,PC=888,PD=6813;//PID²ÎÊı
u16 PID_Parameter[10],Flash_Parameter[10];  //FlashÏà¹ØÊı×é	
u8 temp, humi, humi_dec, temp_dec;
int main(void)
{								  
	Stm32_Clock_Init(9);
	delay_init(72);	 	
	uart_init(72,115200); 
	uart2_init(36,115200);	
	JTAG_Set(JTAG_SWD_DISABLE); 
	JTAG_Set(SWD_ENABLE);
	LED_Init();
	//KEY_Init();
	//DHT11_init();
	/*Encoder_Init_TIM2();           
	Encoder_Init_TIM3();           
	IIC_Init();
	MPU6050_initialize();
	DMP_Init();
	EXTI_Init();  */
	//HC_SR04_init();
	TIM3_Cap_Init(0XFFFF,71);
	LED=0;
 	while(1)
	{/*
		DataScope();
		delay_flag=1;	
		delay_50=0;
		while(delay_flag);	     //Í¨¹ıMPU6050µÄINTÖĞ¶ÏÊµÏÖµÄ50ms¾«×¼ÑÓÊ
		//uart_receive(); */
		//HC_SR04_run();
		Read_Distane();
		printf("%d\n",Distance);
		delay_ms(500);
		LED=~LED;
		//if(DHT11_Read_Data(&humi,&temp,&humi_dec,&temp_dec)){	
		//printf("temp:%d.%d,humi:%d.%d\n",temp,temp_dec,humi,humi_dec);
		//}
		
	}		 
}

