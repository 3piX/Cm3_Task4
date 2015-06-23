/*
 * JoyStick.h
 *
 *  Created on: 22/06/2015
 *      Author: Marc
 */

#ifndef APP_INC_JOYSTICK_H_
#define APP_INC_JOYSTICK_H_

#include "stm32f10x_lib.h"

#define JOY_TOP_INI			512
#define JOY_BOT_INI			512

#define JOY_MOT_HYS			50


#define JOY_DATA_TOP_MOTOR	0
#define JOY_DATA_BOT_MOTOR	1
#define	JOY_DATA_TOP_BOT	2
#define JOY_DATA_BOT_BOT	3


#define ARM_ALPHA_OFFSET	512+360
#define ARM_ROTATE_OFFSET	512
extern u16 joyStickBuff[15];

void readJoyStick();



#endif /* APP_INC_JOYSTICK_H_ */
