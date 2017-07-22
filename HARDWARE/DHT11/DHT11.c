//Use B12 com to transfer data
#include "DHT11.h"
#include "sys.h"
#include "delay.h"
u8 tdata[4]={0x00,0x00,0x00,0x00};
u8 sbuf,check;
void DHT11_Rst(void)	    
{                  
		DHT11_IO_OUT(); 	//SET OUTPUT 
    DHT11_DQ_OUT=0; 	//����DQ 
    delay_ms(18);    	//��������18ms 
    DHT11_DQ_OUT=1; 	//DQ=1 
		delay_us(25);
} 
//�ȴ�DHT11�Ļ�Ӧ 
//����1:δ��⵽DHT11�Ĵ��� 
//����0:���� 
char DHT11_Check(void) 	    
{    
		DHT11_IO_IN();
		if(!DHT11_DQ_IN){
			while(!DHT11_DQ_IN);
			while(DHT11_DQ_IN);
			return 1;
		}
		return 0;
} 

void DHT11_Read_Byte(void) 	  
{ 
	u8 tt,i;
	tt=0;
	for(i = 0;i<8;i++){
		sbuf <<= 1;
		delay_us(20);
		while(!DHT11_DQ_IN);
		delay_us(25);
		tt = 100;
		while(tt++);
		if(DHT11_DQ_IN){
			sbuf |=0x01;
			delay_us(30);
		}
		else{
			sbuf &= 0xfe;
		}
	}	
} 


//��DHT11��ȡһ������ 
//temp:�¶�ֵ(��Χ:0~50��) 
//humi:ʪ��ֵ(��Χ:20%~90%) 
//����ֵ��0,����;1,��ȡʧ�� 
char DHT11_Read_Data(u8 *humi,u8 *temp,u8 *humi_dec,u8 *temp_dec)     
{   
	u8 sum;
	DHT11_Rst(); 
	if(DHT11_Check()){
		//��ȡ40λ���� 
		DHT11_Read_Byte();
		tdata[0]=sbuf;
		DHT11_Read_Byte();
		tdata[1]=sbuf;
		DHT11_Read_Byte();
		tdata[2]=sbuf;		
		DHT11_Read_Byte();
		tdata[3]=sbuf;
		DHT11_Read_Byte();		
		check = sbuf;
		//printf("D0-%d,D1-%d,D2-%d,D3-%d,CHECK-%d\n",tdata[0],tdata[1],tdata[2],tdata[3],check);
		sum = (tdata[0]+tdata[1]+tdata[2]+tdata[3]);		
	}
	if(check == sum){
		*humi = tdata[0];
		*humi_dec = tdata[1];
		*temp = tdata[2];
		*temp_dec = tdata[3];
		return 1;
	}
	else	
		return 0;
} 

char DHT11_init(void){
	RCC->APB2ENR|=1<<3;
	GPIOB->CRH&=0XFFF0FFFF;
	GPIOB->CRH|=0X00030000;
	GPIOB->ODR|=1<<12;
	DHT11_Rst(); 
	return DHT11_Check(); 
}
