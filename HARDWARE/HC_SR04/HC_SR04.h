#ifndef _HC_SR04_H
#define _HC_SR04_H
#include "sys.h"

void HC_SR04_init(void);
void Read_Distane(void);
void TIM3_IRQHandler(void);
#endif
