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

int main(void)
{								  
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
		DataScope();
		delay_flag=1;	
		delay_50=0;
		while(delay_flag);	     //ͨ��MPU6050��INT�ж�ʵ�ֵ�50ms��׼���
		//uart_receive();
	}		 
}

