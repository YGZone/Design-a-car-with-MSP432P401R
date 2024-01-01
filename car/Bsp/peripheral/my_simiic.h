#ifndef _MY_SIMIIC_H_
#define _MY_SIMIIC_H_

#include "headfile.h"


// ��� IIC ����
#define SIMIIC_PORT GPIO_PORT_P2
#define SIMIIC_SCL	GPIO_PIN6															// ����SCL����  ���������Ϊ����IO
#define SIMIIC_SDA	GPIO_PIN7															// ����SDA����  ���������Ϊ����IO

#define SDA				GPIO_getInputPinValue(SIMIIC_PORT,SIMIIC_SDA)
#define SDA0()			GPIO_setOutputLowOnPin(SIMIIC_PORT,SIMIIC_SDA)			// IO������͵�ƽ
#define SDA1()			GPIO_setOutputHighOnPin(SIMIIC_PORT,SIMIIC_SDA)			// IO������ߵ�ƽ
#define SCL0()			GPIO_setOutputLowOnPin(SIMIIC_PORT,SIMIIC_SCL)			// IO������͵�ƽ
#define SCL1()			GPIO_setOutputHighOnPin(SIMIIC_PORT,SIMIIC_SCL)			// IO������ߵ�ƽ
#define DIR_OUT()		GPIO_setAsOutputPin(SIMIIC_PORT,SIMIIC_SDA);			// �������
#define DIR_IN()		GPIO_setAsInputPinWithPullUpResistor(SIMIIC_PORT,SIMIIC_SDA);	// ���뷽��

#define SEEKFREE_ACK	1															// ��Ӧ��
#define SEEKFREE_NACK	0															// ��Ӧ��

typedef enum IIC																	// IIC ģ��
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

