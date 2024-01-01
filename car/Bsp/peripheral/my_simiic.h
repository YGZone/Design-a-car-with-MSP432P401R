#ifndef _MY_SIMIIC_H_
#define _MY_SIMIIC_H_

#include "headfile.h"


// 软件 IIC 定义
#define SIMIIC_PORT GPIO_PORT_P2
#define SIMIIC_SCL	GPIO_PIN6															// 定义SCL引脚  可任意更改为其他IO
#define SIMIIC_SDA	GPIO_PIN7															// 定义SDA引脚  可任意更改为其他IO

#define SDA				GPIO_getInputPinValue(SIMIIC_PORT,SIMIIC_SDA)
#define SDA0()			GPIO_setOutputLowOnPin(SIMIIC_PORT,SIMIIC_SDA)			// IO口输出低电平
#define SDA1()			GPIO_setOutputHighOnPin(SIMIIC_PORT,SIMIIC_SDA)			// IO口输出高电平
#define SCL0()			GPIO_setOutputLowOnPin(SIMIIC_PORT,SIMIIC_SCL)			// IO口输出低电平
#define SCL1()			GPIO_setOutputHighOnPin(SIMIIC_PORT,SIMIIC_SCL)			// IO口输出高电平
#define DIR_OUT()		GPIO_setAsOutputPin(SIMIIC_PORT,SIMIIC_SDA);			// 输出方向
#define DIR_IN()		GPIO_setAsInputPinWithPullUpResistor(SIMIIC_PORT,SIMIIC_SDA);	// 输入方向

#define SEEKFREE_ACK	1															// 主应答
#define SEEKFREE_NACK	0															// 从应答

typedef enum IIC																	// IIC 模块
{
	SIMIIC,
	SCCB
} IIC_type;

void	simiic_delay_set		(uint16 time);
void	simiic_start			(void);
void	simiic_stop				(void);
void	simiic_ack_main			(uint8 ack_main);
void	send_ch					(uint8 c);
uint8	read_ch					(uint8 ack);
void	simiic_write_reg		(uint8 dev_add, uint8 reg, uint8 dat);
void	simiic_write_regs		(uint8 dev_add, uint8 reg, uint8 *dat, uint8 num);
uint8	simiic_read_reg			(uint8 dev_add, uint8 reg, IIC_type type);
void	simiic_read_regs		(uint8 dev_add, uint8 reg, uint8 *dat_add, uint8 num, IIC_type type);
void	simiic_init				(void);









#endif

