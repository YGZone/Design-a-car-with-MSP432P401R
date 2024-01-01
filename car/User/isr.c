
//中断回调

#include "isr.h"


/* GPIO ISR */
void PORT1_IRQHandler(void)
{
    uint32_t status;

    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    /* Toggling the output on the LED */
    if(status & GPIO_PIN1)
    {
        LED_TOGGLE;
    }
}


/* TA0 ISR */
void TA2_N_IRQHandler(void)
{
	int16 int_ch = TA2IV;
	if(int_ch == 0x02)
	{
		encoder0_cnt ++;
		Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1);	
	}
	else if(int_ch == 0x04)
	{
		encoder1_cnt ++;
		Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);
	}
}


uint32 Timer32_Cnt = 0;
/* Timer32 ISR */
void T32_INT1_IRQHandler(void)
{
	Timer32_clearInterruptFlag(TIMER32_BASE);
	Timer32_Cnt +=10;
	/* 100ms任务 */
	if(Timer32_Cnt % 100 == 0)
	{
		Speed_Control();
	}
	/* 300ms任务 */
	if(Timer32_Cnt % 300 == 0)
	{
		ps2gamepad_clear(&PS2);
	}
	/* 清零计数 */
	if(Timer32_Cnt >= 1000)
	{
		Timer32_Cnt = 0;
		LED_TOGGLE;
	}
    Timer32_setCount(TIMER32_BASE,480000);//10ms中断
	Timer32_startTimer(TIMER32_BASE, true);
}


/* 串口中断函数 */
void EUSCIA2_IRQHandler(void)
{
	uint8 datA2 = 0;
	//读取
	datA2 = UART_receiveData(EUSCI_A2_BASE);;
	ps2gamepad_decode(datA2,&PS2);
	UART_clearInterruptFlag(EUSCI_A2_BASE,EUSCI_A_UART_RECEIVE_INTERRUPT);
}

