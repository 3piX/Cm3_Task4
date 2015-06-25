/*
 * JoyStick.c
 *
 *  Created on: 22/06/2015
 *      Author: Marc
 */

#include "JoyStick.h"
#include "ADC.h"
#include "DXL.h"
#include "DXLdef.h"
#include "PC_Com.h"

#define JOY_TOP_ADD			2
#define JOY_BOT_ADD			7
#define	JOY_PUSH_TOP_ADD	1
#define	JOY_PUSH_FRONT_ADD	2






u16 joyStickBuff[15];
u16 oldMotorVal_TOP, oldMotorVal_BOT;
u8	fontMotorToggle = 0;


void readJoyStick()
{

	int i = 0;


	// Read TOP motor from joystick
		DXL_RX_com_buf[4] = 1;
		while((DXL_RX_com_buf[4]))
		{
			DXL_read_byte(JOY_TOP_ADD, PRESENT_POSTION_H);
		}
		DXL_RX_com_buf[4] = 1;

		joyStickBuff[JOY_DATA_TOP_MOTOR] = (DXL_RX_com_buf[5]<<8);

		DXL_RX_com_buf[4] = 1;



	while((DXL_RX_com_buf[4]))
	{
		DXL_read_byte(JOY_TOP_ADD, PRESENT_POSTION_L);
	}
	DXL_RX_com_buf[4] = 1;

	joyStickBuff[JOY_DATA_TOP_MOTOR] |= DXL_RX_com_buf[5];


	// filtering
	if(joyStickBuff[JOY_DATA_TOP_MOTOR] > oldMotorVal_TOP+15 || joyStickBuff[JOY_DATA_TOP_MOTOR] < oldMotorVal_TOP-15)
	{
		joyStickBuff[JOY_DATA_TOP_MOTOR] = oldMotorVal_TOP;

	}
	oldMotorVal_TOP = joyStickBuff[JOY_DATA_TOP_MOTOR];


	// Read BOT motor from joystick
	while((DXL_RX_com_buf[4]))
	{
		DXL_read_byte(JOY_BOT_ADD, PRESENT_POSTION_H);
	}
	DXL_RX_com_buf[4] = 1;

	joyStickBuff[JOY_DATA_BOT_MOTOR] = DXL_RX_com_buf[5]<<8;



	while((DXL_RX_com_buf[4]))
	{
		DXL_read_byte(JOY_BOT_ADD, PRESENT_POSTION_L);
	}
	DXL_RX_com_buf[4] = 1;

	joyStickBuff[JOY_DATA_BOT_MOTOR] |= DXL_RX_com_buf[5];

	// filtering
	if(joyStickBuff[JOY_DATA_BOT_MOTOR] > oldMotorVal_BOT+10 || joyStickBuff[JOY_DATA_BOT_MOTOR] < oldMotorVal_BOT-10)
	{
		joyStickBuff[JOY_DATA_BOT_MOTOR] = oldMotorVal_BOT;

	}
	oldMotorVal_BOT = joyStickBuff[JOY_DATA_BOT_MOTOR];







	// Read PUSH bottons


	if(sampleADC(JOY_PUSH_TOP_ADD) > 100)
	{

		fontMotorToggle = 1;
		joyStickBuff[JOY_DATA_TOP_BOT] = fontMotorToggle;
	}
	else
	{
		joyStickBuff[JOY_DATA_TOP_BOT] = 0;
	}

	if(sampleADC(JOY_PUSH_FRONT_ADD) > 100)
	{
		joyStickBuff[JOY_DATA_BOT_BOT] = 1;
	}
	else
	{
		joyStickBuff[JOY_DATA_BOT_BOT] = 0;
	}

	joyStickBuff[4] = 0;


}

void initJoyStick()
{

	// Read TOP motor from joystick
			DXL_RX_com_buf[4] = 1;
			while((DXL_RX_com_buf[4]))
			{
				DXL_read_byte(JOY_TOP_ADD, PRESENT_POSTION_H);
			}
			DXL_RX_com_buf[4] = 1;

			oldMotorVal_TOP = (DXL_RX_com_buf[5]<<7);

			DXL_RX_com_buf[4] = 1;
			while((DXL_RX_com_buf[4]))
			{
				DXL_read_byte(JOY_TOP_ADD, PRESENT_POSTION_H);
			}
			DXL_RX_com_buf[4] = 1;

			oldMotorVal_TOP += (DXL_RX_com_buf[5]<<7);



		while((DXL_RX_com_buf[4]))
		{
			DXL_read_byte(JOY_TOP_ADD, PRESENT_POSTION_L);
		}
		DXL_RX_com_buf[4] = 1;

		oldMotorVal_TOP |= DXL_RX_com_buf[5];


		// Read BOT motor from joystick
		while((DXL_RX_com_buf[4]))
		{
			DXL_read_byte(JOY_BOT_ADD, PRESENT_POSTION_H);
		}
		DXL_RX_com_buf[4] = 1;

		oldMotorVal_BOT = DXL_RX_com_buf[5]<<7;


		while((DXL_RX_com_buf[4]))
		{
			DXL_read_byte(JOY_BOT_ADD, PRESENT_POSTION_H);
		}
		DXL_RX_com_buf[4] = 1;

		oldMotorVal_BOT += DXL_RX_com_buf[5]<<7;


		while((DXL_RX_com_buf[4]))
		{
			DXL_read_byte(JOY_BOT_ADD, PRESENT_POSTION_L);
		}
		DXL_RX_com_buf[4] = 1;

		oldMotorVal_BOT |= DXL_RX_com_buf[5];

}
