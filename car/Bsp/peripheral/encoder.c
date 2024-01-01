
//步方向编码器读取数值 msp432p401r没有正交编码解码定时器

#include "encoder.h"

volatile uint16 encoder0_cnt = 0;
volatile int16  encoder0_val = 0;
volatile uint16 encoder1_cnt = 0;
volatile int16  encoder1_val = 0;

/* Timer_A Continuous Mode Configuration Parameter */
const Timer_A_ContinuousModeConfig Encoder_continuousModeConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,           // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_24,       // SMCLK/24 = 500KHz
        TIMER_A_TAIE_INTERRUPT_DISABLE,      // Disable Timer ISR
        TIMER_A_SKIP_CLEAR                   // Skup Clear Counter
};

/* Timer_A Capture Mode Configuration Parameter */
const Timer_A_CaptureModeConfig Encoder_captureModeConfig0 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_1,        // CC Register 1
        TIMER_A_CAPTUREMODE_RISING_EDGE,          // Rising Edge
        TIMER_A_CAPTURE_INPUTSELECT_CCIxA,        // CCIxA Input Select
        TIMER_A_CAPTURE_ASYNCHRONOUS,             // Asynchronoused Capture
        TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,  // Enable interrupt
        TIMER_A_OUTPUTMODE_OUTBITVALUE            // Output bit value
};

/* Timer_A Capture Mode Configuration Parameter */
const Timer_A_CaptureModeConfig Encoder_captureModeConfig1 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_2,        // CC Register 2
        TIMER_A_CAPTUREMODE_RISING_EDGE,          // Rising Edge
        TIMER_A_CAPTURE_INPUTSELECT_CCIxA,        // CCIxA Input Select
        TIMER_A_CAPTURE_ASYNCHRONOUS,             // Asynchronoused Capture
        TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,  // Enable interrupt
        TIMER_A_OUTPUTMODE_OUTBITVALUE            // Output bit value
};


// 初始化编码器
void Encoder_Init(void)
{
	//编码器计数部分
	//引脚复用
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN6,
            GPIO_PRIMARY_MODULE_FUNCTION);
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN7,
            GPIO_PRIMARY_MODULE_FUNCTION);
    //配置模式
    Timer_A_initCapture(TIMER_A2_BASE, &Encoder_captureModeConfig0);
	Timer_A_initCapture(TIMER_A2_BASE, &Encoder_captureModeConfig1);
	//配置连续捕获
    Timer_A_configureContinuousMode(TIMER_A2_BASE, &Encoder_continuousModeConfig);
	//配置中断
    Interrupt_enableInterrupt(INT_TA2_N);
	
	//开始捕获
    Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_CONTINUOUS_MODE);
	//方向部分
	GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1,GPIO_PIN7);//left wheel
	GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2,GPIO_PIN3);//right wheel
}


//读取编码器
void Read_Encoder(void)
{
	if(GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN7))
		encoder0_val = encoder0_cnt;
	else
		encoder0_val = -encoder0_cnt;
	if(GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN3))
		encoder1_val = -encoder1_cnt;
	else
		encoder1_val = encoder1_cnt;
	//clear
	encoder0_cnt = 0;
	//clear
	encoder1_cnt = 0;
	
}





