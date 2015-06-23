/************************* (C) COPYRIGHT 2010 ROBOTIS **************************
* File Name          : main.c
* Author             : danceww
* Version            : V0.0.1
* Date               : 08/23/2010
* Description        : Main program body
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x_lib.h"


#include "sys_init.h"
#include "PC_Com.h"
#include "DXL.h"
#include "DXLdef.h"
#include "MotorControl.h"
#include "Zigbee.h"
#include "JoyStick.h"

#include "ADC.h"

#define PORT_LED_AUX			GPIOB
#define PORT_LED_MANAGE			GPIOB
#define PORT_LED_PROGRAM		GPIOB
#define PORT_LED_PLAY			GPIOB
#define PORT_LED_POWER			GPIOC
#define PORT_LED_TX				GPIOC
#define PORT_LED_RX				GPIOC

#define PIN_LED_AUX				GPIO_Pin_12
#define PIN_LED_MANAGE			GPIO_Pin_13
#define PIN_LED_PROGRAM			GPIO_Pin_14
#define PIN_LED_PLAY			GPIO_Pin_15
#define PIN_LED_POWER			GPIO_Pin_13
#define PIN_LED_TX				GPIO_Pin_14
#define PIN_LED_RX				GPIO_Pin_15

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

u32                             Baudrate_DXL = 	1000000;
u32                             Baudrate_PC = 57600;
u16								ADCres_buf[50];
u16								ADCres_buf_index = 0;
u16 							diff = 0;
u8								wallTrackSide = 0;
u8								IRsweepDone, sweepDirection = 0;
vu16								count = 214;
u8								rightTrackOffset;

const u16 angleLUT[601] = {
	#include "lookup.hex"
};

void __ISR_DELAY(void);




int main(void)
{

	u16 j = 0;
    /* System Clocks Configuration */
	RCC_Configuration();

	/* NVIC configuration */
	NVIC_Configuration();

	/* GPIO configuration */
	GPIO_Configuration(); // Setup of IOs
	//GPIO_Start();

	SysTick_Configuration(); // used for delay function (PC_Com.c)

	DXL_init(1000000);

	USART_Configuration(USART_PC, Baudrate_PC);



	DXL_RX_com_buf[14] = 0;

	init_ADC();



	initZigbee();




	while(1)
	{

		readJoyStick();
		

		DXL_send_word(5, GOAL_POSITION_L, angleLUT[joyStickBuff[JOY_DATA_BOT_MOTOR]]);
		uDelay(100);
		DXL_send_word(4, GOAL_POSITION_L, (joyStickBuff[JOY_DATA_BOT_MOTOR] - (JOY_BOT_INI - ARM_ALPHA_OFFSET)));


	//	TxDWord16(joyStickBuff[JOY_DATA_BOT_MOTOR]-(JOY_BOT_INI - ARM_ALPHA_OFFSET));
	//	TxDByte_PC("\r");
		DXL_send_word(8, GOAL_POSITION_L, (joyStickBuff[JOY_DATA_TOP_MOTOR] - (JOY_TOP_INI - ARM_ROTATE_OFFSET)));

	}


	return 0;
}


void __TIM2_ISR()
{
	if(TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
	{


		ADCres_buf_index++;
		TIM2->SR &= ~TIM_IT_CC1;
		TIM2->CNT = 0;

		TIM2->CR1 &= ~TIM_CR1_CEN;
	}
}


void __ISR_DELAY(void)
{
	if (gwTimingDelay != 0x00)
		gwTimingDelay--;
}




