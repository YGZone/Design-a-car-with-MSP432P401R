
#include "pid.h"



/* ������ʼ�� */
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



/*------------------------��ͨ����ʽpid-------------------------*/
SpeedPIDTypedef SpeedPIDLeft,SpeedPIDRight;
int16 SimpleIncremental_PID(SpeedPIDTypedef *pid,int16 _exval,int16 _nowval)
{
	//����
	pid->exval = _exval;
	pid->nowval = _nowval;
	//��ǰ���
	pid->nowError =  pid->exval - pid->nowval;
	//����
	pid->increase = 
		pid->kp * (float)(pid->nowError - pid->lastError) +
		pid->ki * (float)pid->nowError +
		pid->kd * (float)(pid->nowError - 2 * pid->lastError + pid->beforError);
	//�������
	pid->lastError = pid->nowError;
	pid->beforError = pid->lastError;
	pid->out += (int16)pid->increase;
	//���Ʒ���
	pid->out = range_protect(pid->out,(int32)pid->minout,(int32)pid->maxout);
	//���
	return pid->out;
}



