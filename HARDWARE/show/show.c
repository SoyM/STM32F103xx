#include "show.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
unsigned char i;          //计数变量
unsigned char Send_Count; //串口需要发送的数据个数
/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
/**************************************************************************
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
		
		//=============显示编码器1=======================//	
		                      OLED_ShowString(00,20,"Enco1");
		if( Encoder_Left<0)		OLED_ShowString(45,20,"-"),
		                      OLED_ShowNumber(65,20,-Encoder_Left,5,12);
		else                 	OLED_ShowString(45,20,"+"),
		                      OLED_ShowNumber(65,20, Encoder_Left,5,12);
  	//=============显示编码器2=======================//		
		                      OLED_ShowString(00,30,"Enco2");
		if(Encoder_Right<0)		OLED_ShowString(45,30,"-"),
		                      OLED_ShowNumber(65,30,-Encoder_Right,5,12);
		else               		OLED_ShowString(45,30,"+"),
		                      OLED_ShowNumber(65,30,Encoder_Right,5,12);	
			//=============显示角度=======================//
		                      OLED_ShowString(0,40,"Angle_X");
		if(Pitch<0)		OLED_ShowNumber(75,40,Pitch+360,3,12);
		else					        OLED_ShowNumber(75,40,Pitch,3,12);
			//=============显示角度=======================//
			                      OLED_ShowString(0,50,"Angle_Y");
		if(Roll<0)		OLED_ShowNumber(75,50,Roll+360,3,12);
		else					        OLED_ShowNumber(75,50,Roll,3,12);
		//=============刷新=======================//
		OLED_Refresh_Gram();	
	}
**************************************************************************/
/**************************************************************************
函数功能：向APP发送数据
入口参数：无
返回  值：无
作    者：平衡小车之家
**************************************************************************/
void APP_Show(void)
{    
	  static u8 flag;
	  int app_2,app_3;
		app_3=Encoder_Right*1.1; if(app_3<0)app_3=-app_3;			                   //对编码器数据就行数据处理便于图形化
		app_2=Encoder_Left*1.1;  if(app_2<0)app_2=-app_2;
	  flag=!flag;
	if(PID_Send==1)//发送PID参数
	{
		printf("{C%d:%d:%d:%d:%d:%d:%d:%d:%d}$",(int)(PA),(int)(PB),(int)(PC),(int)(PD),0,0,0,0,0);//打印到APP上面	
		PID_Send=0;	
	}	
   else	if(flag==0)// 
   printf("{A%d:%d:%d:%d}$",(u8)app_2,(u8)app_3,66,(int)Angle_Balance); //打印到APP上面
	 else
	 printf("{B%d:%d:%d}$",(int)Pitch,(int)Roll,(int)Yaw);//打印到APP上面 显示波形
}
/**************************************************************************
函数功能：虚拟示波器往上位机发送数据 关闭显示屏
入口参数：无
返回  值：无
作    者：平衡小车之家
**************************************************************************/

void DataScope(void)
{   
		DataScope_Get_Channel_Data( Pitch, 1 );       
		DataScope_Get_Channel_Data( -Roll, 2 );       
		DataScope_Get_Channel_Data( -Yaw, 3 );            
//		DataScope_Get_Channel_Data( 0 , 4 );   
//		DataScope_Get_Channel_Data(0, 5 ); //用您要显示的数据替换0就行了
//		DataScope_Get_Channel_Data(0 , 6 );//用您要显示的数据替换0就行了
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
