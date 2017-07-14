#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
#define PI 3.14159265
int EXTI3_IRQHandler(void);
void Key(void);
void Get_Angle(u8 way);
int myabs(int a);
#endif
