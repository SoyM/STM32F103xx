#include "sys.h"
u8 Way_Angle=1;                             //��ȡ�Ƕȵ��㷨��1����Ԫ�� 
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_sudu=2; //����ң����صı���
u8 Flag_Stop=1,Flag_Show=1;                 //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
int Encoder_Left,Encoder_Right;             //���ұ��������������
int Moto1,Moto2;                            //���PWM���� Ӧ��Motor�� ��Moto�¾�	
int Temperature;                            //��ʾ�¶�
int Voltage;                                //��ص�ѹ������صı���
float Angle_Balance,Gyro_Balance,Gyro_Turn; //ƽ����� ƽ�������� ת��������
float Show_Data_Mb;                         //ȫ����ʾ������������ʾ��Ҫ�鿴������
u32 Distance;                               //���������
u8 delay_50,delay_flag,Bi_zhang=0,PID_Send,Flash_Send;   //Ĭ�������
float Acceleration_Z;                       //Z����ٶȼ�  
float PA=100,PB=500,PC=888,PD=6813;//PID����
u16 PID_Parameter[10],Flash_Parameter[10];  //Flash�������	
u8 temp, humi, humi_dec, temp_dec;
u8 R=0x00,G=0x00,B=0x00;
float Max=0,Min=0;
float Rhsv=0,Ghsv=0,Bhsv=0;
float H=0,S=0,V=0;

int main(void)
{								  
	Stm32_Clock_Init(9);
	delay_init(72);	 		
	JTAG_Set(JTAG_SWD_DISABLE); 
	JTAG_Set(SWD_ENABLE);
	LED_Init();
	KEY_Init();
	//OLED_Init();  
	uart_init(72,128000);
	printf("begin");
	//uart2_init(36,9600);
	//MiniBalance_PWM_Init(7199,0);
	//Encoder_Init_TIM2();           
	//Encoder_Init_TIM3();           
	//IIC_Init();
	//MPU6050_initialize();
	//DMP_Init();
	//Flash_Read(); 
	EXTI_Init();  
	//DHT11_init();
	//HC_SR04_init();
	//TIM3_Cap_Init(0XFFFF,71);
	//-tcs3200_init();
	//-whitebalance();
	//LED=0;
	//InitRc522();
 	while(1)
	{
/*	if(Flash_Send==1)          //д��PID������Flash,��app���Ƹ�ָ��
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
		while(delay_flag);	     //ͨ��MPU6050��INT�ж�ʵ�ֵ�50ms��׼��ʱ */
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
		///G = tcs3200_GREEN();	//ȡRGBֵ
		///B = tcs3200_BLUE();	 
		///en=1;
		///printf("R-%d,G-%d,B-%d\n",R,G,B);
		delay_ms(1000);
	}		 
}

