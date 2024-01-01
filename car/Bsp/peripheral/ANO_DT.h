/*
 * @Editor      : zyg
 * @Date        : Do not edit
 * @Version     : MDK5.32
 * @LastEditTime: 2020-12-23 15:53:26
 * @Description : ������λ�������ļ�
 * @Attention   : ע����ղ�����Ҫ������Ҫ������ֲ
 */

#ifndef _ANO_DT_
#define _ANO_DT_

#include "headfile.h"


#define ANO_UART_BAUD        115200
#define ANO_UART_DMA_CHANNEL DMA1_Channel2
#define ANO_UART_DMA_IRQn    DMA1_Channel2_IRQn


//���ݲ�ֺ궨�壬�ڷ��ʹ���1�ֽڵ���������ʱ������int16��float�ȣ���Ҫ�����ݲ�ֳɵ����ֽڽ��з���
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

//Ŀ��ʶ������
#define MYHWADDR	0x05    //�ؿ���
#define SWJADDR		0xAF    

//��������
#define USERDATA_1   0
#define USERDATA_2   1
#define USERDATA_3   2
#define USERDATA_4   3
#define USERDATA_5   4
#define USERDATA_6   5
#define USERDATA_7   6
#define USERDATA_8   7
#define USERDATA_9   8
#define USERDATA_10  9
#define USERDATA_11  10
#define USERDATA_12  11
#define USERDATA_13  12
#define USERDATA_14  13
#define USERDATA_15  14
#define USERDATA_16  15
#define USERDATA_17  16
#define USERDATA_18  17
#define USERDATA_19  18
#define USERDATA_20  19

//�������ݴ洢
extern short waveform[20];
//������ʾ״̬
extern unsigned  char WAVEFORM_ENABLE ;
#define PID1        0
#define PID2        1
#define PID3        2
#define PID4        3
#define PID5        4
#define PID6        5
#define PID7        6
#define PID8        7
#define PID9        8
#define PID10       9
#define PID11       10
#define PID12       11
#define PID13       12
#define PID14       13
#define PID15       14
#define PID16       15
#define PID17       16
#define PID18       17

//ָ��
#define READ_PARAM    0xE0   //��ȡ����ָ��
#define WRITE_PARAM   0xE1   //д�����ָ��

//��������
typedef struct 
{
    unsigned int P;
    unsigned int I;
    unsigned int D;
}pid_param_type;
extern pid_param_type pid_param[25];

extern unsigned char cmd_buff[17];
//fun
void ANO_DT_Init(void);
void Waveform_Write(void);
void Send_Waveform(void);
#endif


