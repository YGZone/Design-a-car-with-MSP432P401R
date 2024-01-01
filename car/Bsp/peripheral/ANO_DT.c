/*
 * @Editor      : zyg
 * @Date        : Do not edit
 * @Version     : MDK5.32
 * @LastEditTime: 2020-12-23 16:03:17
 * @Description : ������λ�������ļ�
 * @Attention   : ע����ղ��ְ�����Ҫ������ֲ
 */

#include "ANO_DT.h"

//��Ҫ����
#define   WAVEFORM_COUNT   1        //�м�·���� �ᷢ��ǰx·����  

short  waveform[20];         //���λ���
unsigned char data_to_receive[100]; //���յĻ���
unsigned char data_to_send[100];	//�������ݻ���    
unsigned char WAVEFORM_ENABLE = 1;


pid_param_type pid_param[25];



//��ʼ��
const eUSCI_UART_ConfigV1 uartConfig =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source = 12MHz
        78,                                      // BRDIV = 78
        2,                                       // UCxBRF = 2
        0,                                       // UCxBRS = 0
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,  // Oversampling
        EUSCI_A_UART_8_BIT_LEN                   // 8 bit data length
};


/**
 * @editior: zyg
 * @brief  : none
 * @param  : none
 * @return : NULL
 * @example: void ANO_DT_Init(void)
 */
void ANO_DT_Init(void)
{
	/* Selecting P1.2 and P1.3 in UART mode and P1.0 as output (LED) */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
             GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configuring UART Module */
    UART_initModule(EUSCI_A2_BASE, &uartConfig);
	
	/* Enable UART module */
    UART_enableModule(EUSCI_A2_BASE);
	
	/* Enable Interrupt */
	UART_enableInterrupt(EUSCI_A2_BASE,EUSCI_A_UART_RECEIVE_INTERRUPT);
    Interrupt_enableInterrupt(INT_EUSCIA2);
}


/**
 * @editior: zyg
 * @brief  : none
 * @param  : ��������ַ
 * @param  : ������鳤��
 * @return : NULL
 * @example: ANO_DT_Send_Data(my_data , sizerof(my_data))
 */
void ANO_DT_Send_Data(unsigned  char *_dataToSend , unsigned int length)
{
	while(length --)
	{
		UART_transmitData(EUSCI_A2_BASE,*_dataToSend ++);
	}
}


/**
 * @editior: zyg
 * @brief  : ���в������ݵ�д��
 * @param  : NULL
 * @return : NULL
 * @example: none
 */
void Waveform_Write(void)
{
    waveform[USERDATA_1]   = 100;
    waveform[USERDATA_2]   = 0;
    waveform[USERDATA_3]   = 0;
    waveform[USERDATA_4]   = 0;
    waveform[USERDATA_5]   = 0;
    waveform[USERDATA_6]   = 0;
    waveform[USERDATA_7]   = 0;
    waveform[USERDATA_8]   = 0;
	waveform[USERDATA_9]   = 0;
    waveform[USERDATA_10]  = 0;
    waveform[USERDATA_11]  = 0;
    waveform[USERDATA_12]  = 0; 
    waveform[USERDATA_13]  = 0;
    waveform[USERDATA_14]  = 0;
    waveform[USERDATA_15]  = 0;
    waveform[USERDATA_16]  = 0;
    waveform[USERDATA_17]  = 0;
    waveform[USERDATA_18]  = 0;
    waveform[USERDATA_19]  = 0;
    waveform[USERDATA_20]  = 0;
    //send
    Send_Waveform();
}


/**
 * @editior: zyg
 * @brief  : ���ô˺���,������λ������20·����,ÿһ·���ξ�Ϊshort�ͱ���
 * @param  : none
 * @return : NULL
 * @example: Send_Waveform();
 */
void Send_Waveform(void)
{
    unsigned char _cnt = 0;
	if(WAVEFORM_ENABLE == 1)
	{
		data_to_send[_cnt++]=0xAA;    //ͷ�ֽ�
		data_to_send[_cnt++]=MYHWADDR;//������ַ
		data_to_send[_cnt++]=SWJADDR; //��λ����ַ
		data_to_send[_cnt++]=0xF1;    //���ݲ��η���ָ��,ֻ����F1��һ֡
		data_to_send[_cnt++]=0;       //��Ч�����ֽ���
		//�������ݲ�������
		for(unsigned char i = 0;i <WAVEFORM_COUNT;i ++)
		{
			// data_to_send[_cnt++]=BYTE3(waveform[i]);
			// data_to_send[_cnt++]=BYTE2(waveform[i]);
			data_to_send[_cnt++]=BYTE1(waveform[i]);
			data_to_send[_cnt++]=BYTE0(waveform[i]);
		}
		data_to_send[4] = _cnt-5;//��Ч�����ֽ�
		unsigned char sum = 0;//��У��
		for(unsigned char i=0;i<_cnt;i++)
			sum += data_to_send[i];
		data_to_send[_cnt++]=sum;
		//���ڷ������� ///////////////////д������
		ANO_DT_Send_Data(data_to_send,_cnt);
	}
}

/**
 * @editior: zyg
 * @brief  : ÿ�ε�����ȡ�ɿ�ʱ�˺������Զ�����
 * @param  : NULL
 * @return : NULL
 * @example: Read_Params_of_MCU()
 * @attention: �ڴ˺����м�����Ҫ��ȡ�ı���
 */
void Read_Params_of_MCU(void)
{
    //��һ��PID һ��������18��ɹ�����
    pid_param[PID1].P = 10;
    pid_param[PID1].I = 11;
    pid_param[PID1].D = 12;
    pid_param[PID2].P = 22;
    pid_param[PID2].I = 44;
    pid_param[PID2].D = 66;
}


/**
 * @editior: zyg
 * @brief  : ÿ�ε���д��ɿ�ʱ�˺���������
 * @param  : NULL
 * @return : NULL
 * @example: none
 */
void Write_Params_of_MCU(void)
{
    //��һ��PID һ��������18��ɹ�����
	
}




