/*************************************************************************************
 
	@author 		nefu_zhaoyanguo
	@date 			2021.08.26
	@instruction 	write for nefuer for 2021 ti cup 
	@attention 		good luck to you!
	@CSDN			https://blog.csdn.net/qq_44151690/article/details/119740816?spm=1001.2014.3001.5501
	
*************************************************************************************/


/* Standard Includes */
#include "headfile.h"



int main(void)
{
    /* Stop Watchdog  */
	WDT_A_holdTimer();
	System_Init();
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
    while(1)
    {
//		MotorPWM_Test();
//		Send_Waveform();
//		delay_ms(100);
		Car_Control();
		delay_ms(40);
    }
}




