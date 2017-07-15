#include "control.h"	
#include "filter.h"	
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
/**************************************************************************
�������ܣ����еĿ��ƴ��붼��������
         5ms��ʱ�ж���MPU6050��INT���Ŵ���
         �ϸ�֤���������ݴ����ʱ��ͬ��				 
**************************************************************************/
int EXTI3_IRQHandler(void) 
{    
	 if(PBin(3)==0)		
	{   
		  EXTI->PR=1<<3;                                                      //===���LINE3�ϵ��жϱ�־λ      
		   if(delay_flag==1)
		  {
				 if(++delay_50==10)	 
					 delay_50=0,delay_flag=0;                     //���������ṩ50ms�ľ�׼��ʱ
			 }
		  Encoder_Left=Read_Encoder(2);                                      //===��ȡ��������ֵ
			Encoder_Right=Read_Encoder(3);                                      //===��ȡ��������ֵ
	  	Get_Angle(Way_Angle);                                               //===������̬	                                             
			Led_Flash(100);
	}       	
	 return 0;	  
} 



/**************************************************************************
�������ܣ������޸�С������״̬ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Key(void)
{	
	u8 tmp;
	tmp=click_N_Double(50); 
	if(tmp==1)Flag_Show=!Flag_Show;//˫������С������ʾ״̬
	//if(tmp==2)Flag_Stop=!Flag_Stop;//
}

	
/**************************************************************************
�������ܣ���ȡ�Ƕ� �����㷨�������ǵĵ�У�����ǳ����� 
��ڲ�������ȡ�Ƕȵ��㷨 1��DMP  2�������� 3�������˲�
����  ֵ����
**************************************************************************/
void Get_Angle(u8 way)
{ 
		float Accel_Y,Accel_X,Accel_Z,Gyro_Y,Gyro_Z;
	  Temperature=Read_Temperature();      //===��ȡMPU6050�����¶ȴ��������ݣ����Ʊ�ʾ�����¶ȡ�
	  if(way==1){                           //===DMP�Ķ�ȡ�����ݲɼ��ж����ѵ�ʱ���ϸ���ѭʱ��Ҫ��
				Read_DMP();                      //===��ȡ���ٶȡ����ٶȡ����
				Angle_Balance=Pitch;             //===����ƽ�����
				Gyro_Balance=gyro[1];            //===����ƽ����ٶ�
				Gyro_Turn=gyro[2];               //===����ת����ٶ�
				 Acceleration_Z=accel[2];         //===����Z����ٶȼ�
		}else{
				Gyro_Y=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_L);    //��ȡY��������
				Gyro_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //��ȡZ��������
				Accel_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_L); //��ȡX����ٶȼ�
				Accel_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L); //��ȡZ����ٶȼ�
				if(Gyro_Y>32768)  Gyro_Y-=65536;                       //��������ת��  Ҳ��ͨ��shortǿ������ת��
				if(Gyro_Z>32768)  Gyro_Z-=65536;                       //��������ת��
				if(Accel_X>32768) Accel_X-=65536;                      //��������ת��
				if(Accel_Z>32768) Accel_Z-=65536;                      //��������ת��
				Gyro_Balance=-Gyro_Y;                                  //����ƽ����ٶ�
				Accel_Y=atan2(Accel_X,Accel_Z)*180/PI;                 //�������	
		    Gyro_Y=Gyro_Y/16.4;                                    //����������ת��	
				if(Way_Angle==2){
						Kalman_Filter(Accel_Y,-Gyro_Y);//�������˲�	
				}
				else if(Way_Angle==3){   
						Yijielvbo(Accel_Y,-Gyro_Y);    //�����˲�
				}
				Angle_Balance=angle;                                   //����ƽ�����
				Gyro_Turn=Gyro_Z;                                      //����ת����ٶ�
				Acceleration_Z=Accel_Z;                                //===����Z����ٶȼ�	
		}
}
/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
