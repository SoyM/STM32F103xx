#ifndef __TCS3200_H
#define __TCS3200_H
#include "sys.h"

extern u16 amount;

extern u8 Rgena,Ggena,Bgena;
extern u16 Ramount,Gamount,Bamount;


#define S2 PBout(12)
#define S3 PBout(13)
#define en PBout(1)
#define OUT PBin(0)

void tcs3200_init(void);
void whitebalance(void);
u16 tcs3200_RED(void);
u16 tcs3200_GREEN(void);
u16 tcs3200_BLUE(void);

#endif

