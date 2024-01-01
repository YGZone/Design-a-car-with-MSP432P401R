
#include "pid.h"



/* 参数初始化 */
void pid_param_init(void)
{
	SpeedPIDLeft.maxout = 10000;
	SpeedPIDLeft.minout = -10000;
	SpeedPIDLeft.kp = 5.0f;
	SpeedPIDLeft.ki = 20.0f;
	SpeedPIDRight.maxout = 10000;
	SpeedPIDRight.minout = -10000;
	SpeedPIDRight.kp = 5.0f;
	SpeedPIDRight.ki = 20.0f;
}



/*------------------------普通增量式pid-------------------------*/
SpeedPIDTypedef SpeedPIDLeft,SpeedPIDRight;
int16 SimpleIncremental_PID(SpeedPIDTypedef *pid,int16 _exval,int16 _nowval)
{
	//运算
	pid->exval = _exval;
	pid->nowval = _nowval;
	//当前误差
	pid->nowError =  pid->exval - pid->nowval;
	//增量
	pid->increase = 
		pid->kp * (float)(pid->nowError - pid->lastError) +
		pid->ki * (float)pid->nowError +
		pid->kd * (float)(pid->nowError - 2 * pid->lastError + pid->beforError);
	//更新误差
	pid->lastError = pid->nowError;
	pid->beforError = pid->lastError;
	pid->out += (int16)pid->increase;
	//限制幅度
	pid->out = range_protect(pid->out,(int32)pid->minout,(int32)pid->maxout);
	//输出
	return pid->out;
}



