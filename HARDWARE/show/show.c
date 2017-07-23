#include "show.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
unsigned char i;          //��������
unsigned char Send_Count; //������Ҫ���͵����ݸ���
/**************************************************************************
�������ܣ�OLED��ʾ
��ڲ�������
����  ֵ����
**************************************************************************/

void oled_show(void)
{

													OLED_ShowString(00,0,"PA");
		if( PA<0)	           	OLED_ShowString(15,0,"-"),
		                      OLED_ShowNumber(30,0,-PA,5,12);
		else                 	OLED_ShowString(15,0,"+"),
		                      OLED_ShowNumber(30,0, PA,5,12);
		
				                  OLED_ShowString(65,0,"PB");
		if( PB<0)	           	OLED_ShowString(80,0,"-"),
		                      OLED_ShowNumber(95,0,-PB,5,12);
		else                 	OLED_ShowString(80,0,"+"),
		                      OLED_ShowNumber(95,0, PB,5,12);
		
				                  OLED_ShowString(00,10,"PC");
		if( PC<0)	           	OLED_ShowString(15,10,"-"),
		                      OLED_ShowNumber(30,10,-PC,5,12);
		else                 	OLED_ShowString(15,10,"+"),
		                      OLED_ShowNumber(30,10, PC,5,12);
		
				                  OLED_ShowString(65,10,"PD");
		if( PD<0)	           	OLED_ShowString(80,10,"-"),
		                      OLED_ShowNumber(95,10,-PD,5,12);
		else                 	OLED_ShowString(80,10,"+"),
		                      OLED_ShowNumber(95,10, PD,5,12);
		
		//=============��ʾ������1=======================//	
		                      OLED_ShowString(00,20,"Enco1");
		if( Encoder_Left<0)		OLED_ShowString(45,20,"-"),
		                      OLED_ShowNumber(65,20,-Encoder_Left,5,12);
		else                 	OLED_ShowString(45,20,"+"),
		                      OLED_ShowNumber(65,20, Encoder_Left,5,12);
  	//=============��ʾ������2=======================//		
		                      OLED_ShowString(00,30,"Enco2");
		if(Encoder_Right<0)		OLED_ShowString(45,30,"-"),
		                      OLED_ShowNumber(65,30,-Encoder_Right,5,12);
		else               		OLED_ShowString(45,30,"+"),
		                      OLED_ShowNumber(65,30,Encoder_Right,5,12);	
			//=============��ʾ�Ƕ�=======================//
		                      OLED_ShowString(0,40,"Angle_X");
		if(Pitch<0)		OLED_ShowNumber(75,40,Pitch+360,3,12);
		else					        OLED_ShowNumber(75,40,Pitch,3,12);
			//=============��ʾ�Ƕ�=======================//
			                      OLED_ShowString(0,50,"Angle_Y");
		if(Roll<0)		OLED_ShowNumber(75,50,Roll+360,3,12);
		else					        OLED_ShowNumber(75,50,Roll,3,12);
									OLED_ShowString(96,50,"SoyM");
		//=============ˢ��=======================//
		OLED_Refresh_Gram();	
	}

/**************************************************************************
�������ܣ���APP��������
��ڲ�������
����  ֵ����
��    �ߣ�ƽ��С��֮��
**************************************************************************/
void APP_Show(void)
{    
	  static u8 flag;
	  int app_2,app_3;
		app_3=Encoder_Right*1.1; if(app_3<0)app_3=-app_3;			                   //�Ա��������ݾ������ݴ������ͼ�λ�
		app_2=Encoder_Left*1.1;  if(app_2<0)app_2=-app_2;
	  flag=!flag;
	if(PID_Send==1)//����PID����
	{
		printf("{C%d:%d:%d:%d:%d:%d:%d:%d:%d}$",(int)(PA),(int)(PB),(int)(PC),(int)(PD),0,0,0,0,0);//��ӡ��APP����	
		PID_Send=0;	
	}	
   else	if(flag==0)// 
   printf("{A%d:%d:%d:%d}$",(u8)app_2,(u8)app_3,66,(int)Angle_Balance); //��ӡ��APP����
	 else
	 printf("{B%d:%d:%d}$",(int)Pitch,(int)Roll,(int)Yaw);//��ӡ��APP���� ��ʾ����
}
/**************************************************************************
�������ܣ�����ʾ��������λ���������� �ر���ʾ��
��ڲ�������
����  ֵ����
��    �ߣ�ƽ��С��֮��
**************************************************************************/

void DataScope(void)
{   
		DataScope_Get_Channel_Data( Pitch, 1 );       
		DataScope_Get_Channel_Data( -Roll, 2 );       
		DataScope_Get_Channel_Data( -Yaw, 3 );            
//		DataScope_Get_Channel_Data( 0 , 4 );   
//		DataScope_Get_Channel_Data(0, 5 ); //����Ҫ��ʾ�������滻0������
//		DataScope_Get_Channel_Data(0 , 6 );//����Ҫ��ʾ�������滻0������
//		DataScope_Get_Channel_Data(0, 7 );
//		DataScope_Get_Channel_Data( 0, 8 ); 
//		DataScope_Get_Channel_Data(0, 9 );  
//		DataScope_Get_Channel_Data( 0 , 10);
		Send_Count = DataScope_Data_Generate(3);
		for( i = 0 ; i < Send_Count; i++) 
		{
		while((USART1->SR&0X40)==0);  
		USART1->DR = DataScope_OutPut_Buffer[i]; 
		}
}
