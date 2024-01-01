#ifndef _PID_H_
#define _PID_H_


#include "headfile.h"

//普通速度环 基本速度控制
//简易增量式PID
typedef struct
{
	int16 exval;
	int16 nowval;
	float kp;
	float ki;
	float kd;
	int16 nowError;
	float increase;
	int16 lastError;
	int16 beforError;
	int16 out;
	float maxout;
	float minout;
}SpeedPIDTypedef;

extern SpeedPIDTypedef SpeedPIDLeft,SpeedPIDRight;


void pid_param_init(void);
int16 SimpleIncremental_PID(SpeedPIDTypedef *pid,int16 _exval,int16 _nowval);













#endif

