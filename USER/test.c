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

int main(void)
{								  
	u16 t,len,times;
	Stm32_Clock_Init(9);	
	uart_init(72,115200); 	
	delay_init(72);	   	 	 
	LED_Init();
	Encoder_Init_TIM2();           
	Encoder_Init_TIM3();           
	IIC_Init();
	MPU6050_initialize();
	DMP_Init();
	EXTI_Init();
 	while(1)
	{
		Led_Flash(100);
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3FFF;//µÃµ½´Ë´Î½ÓÊÕµ½µÄÊı¾İ³¤¶È
			printf("\r\nÄú·¢ËÍµÄÏûÏ¢Îª:\r\n\r\n");
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);//µÈ´ı·¢ËÍ½áÊø
			}
			printf("\r\n\r\n");//²åÈë»»ĞĞ
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%200==0)printf("ÇëÊäÈëÊı¾İ,ÒÔ»Ø³µ¼ü½áÊø\r\n");  
			delay_ms(10);   
		}
		DataScope();
		delay_flag=1;	
		delay_50=0;
		while(delay_flag);	     //Í¨¹ıMPU6050µÄINTÖĞ¶ÏÊµÏÖµÄ50ms¾«×¼ÑÓÊ
		
	}		 
}

