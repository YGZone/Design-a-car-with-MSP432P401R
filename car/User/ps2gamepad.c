
#include "ps2gamepad.h"

ps2datatypedef PS2;

/* ps2手柄解码程序 */
void ps2gamepad_decode(uint8 dat,ps2datatypedef *p)
{
	/* 摇杆接收模式 */
	//if(p->l_rocker == 0 && )
	/* 非摇杆接收模式 */
	if(dat == 'A')
		p->l_up = 1;
	else if(dat == 'B')
		p->l_down = 1;
	else if(dat == 'C')
		p->l_left = 1;
	else if(dat == 'D')
		p->l_right = 1;
}




/* ps2手柄状态清零 */
void ps2gamepad_clear(ps2datatypedef *p)
{
	p-> l_up = 0;
	p-> l_down = 0;
	p-> l_left = 0;
	p-> l_right=0;
	p-> l_1=0;
	p-> l_2=0;
	p-> l_rocker=0;
	p-> l_rocker_lr=128;
	p-> l_rocker_ud=128;
	p-> r_up=0;
	p-> r_down=0;
	p-> r_left=0;
	p-> r_right=0;
	p-> r_1=0;
	p-> r_2=0;
	p-> r_rocker=0;
	p-> r_rocker_lr=128;
	p-> r_rocker_ud=128;
}



