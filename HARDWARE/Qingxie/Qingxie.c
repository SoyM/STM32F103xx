#include "Qingxie.h"
#define D0 PBin(7) 

void Qingxie_Init(void){			
	RCC->APB2ENR|=1<<3;//先使能外设IO PORTB时钟 							 
	GPIOB->CRL&=0X0FFFFFFF;
	GPIOB->CRL|=0X80000000;	   
}

char Qingxie_check(void){
	if(D0){
		printf("正常");
		return 1;
	}else{
		printf("超过阈值");
		return 0;
	}	
}
