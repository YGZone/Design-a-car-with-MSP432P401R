#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "headfile.h"


extern int16 pwm_l,pwm_r;
extern int16 speed_l,speed_r;

void Motor_Timer_Init(void);
void MotorPWM_Test(void);
uint8 SpeedSet(int16 LM,int16 RM);






#endif


