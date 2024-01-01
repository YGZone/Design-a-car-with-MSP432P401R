#ifndef _ENCODER_H_
#define _ENCODER_H_


#include "headfile.h"





//statement
extern volatile uint16 encoder0_cnt;
extern volatile int16  encoder0_val;
extern volatile uint16 encoder1_cnt;
extern volatile int16  encoder1_val;

//func
void Encoder_Init(void);
void Read_Encoder(void);





#endif

