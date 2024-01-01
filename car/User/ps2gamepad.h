#ifndef _PS2GAMEPAD_H_
#define _PS2GAMEPAD_H_


#include "headfile.h"

typedef struct 
{
	uint8 l_up;
	uint8 l_down;
	uint8 l_left;
	uint8 l_right;
	uint8 l_1;
	uint8 l_2;
	uint8 l_rocker;
	uint8 l_rocker_lr;
	uint8 l_rocker_ud;
	uint8 r_up;
	uint8 r_down;
	uint8 r_left;
	uint8 r_right;
	uint8 r_1;
	uint8 r_2;
	uint8 r_rocker;
	uint8 r_rocker_lr;
	uint8 r_rocker_ud;
}ps2datatypedef;

extern ps2datatypedef PS2;


void ps2gamepad_decode(uint8 dat,ps2datatypedef *p);
void ps2gamepad_clear(ps2datatypedef *p);









#endif

