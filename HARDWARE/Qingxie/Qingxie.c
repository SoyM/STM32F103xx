#include "Qingxie.h"
#define D0 PBin(7) 

void Qingxie_Init(void){			
	RCC->APB2ENR|=1<<3;//��ʹ������IO PORTBʱ�� 							 
	GPIOB->CRL&=0X0FFFFFFF;
	GPIOB->CRL|=0X80000000;	   
}

char Qingxie_check(void){
	if(D0){
		printf("����");
		return 1;
	}else{
		printf("������ֵ");
		return 0;
	}	
}
