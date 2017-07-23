//超声波测距模块
#include "HC_SR04.h"

#define HC_ECHO PBin(12)
#define HC_TRIG PBout(13)

void HC_SR04_init(void){
	RCC->APB2ENR|=1<<3;
	GPIOB->CRH&=0XFF00FFFF;
	GPIOB->CRH|=0X00380000;
	//GPIOB->ODR|=1<<12;
}

void HC_SR04_run(void){
	u8 retry=0;
	float s;
	HC_TRIG=1;
	delay_us(20);
	HC_TRIG=0;
	while(!HC_ECHO);
	while(HC_ECHO){
		retry++;
		//printf("%d\n",retry);
	}
	s=(retry*1.87)/100;
	printf("s-%f\n",s);
	
}
