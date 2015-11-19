/*
 * buttons.h
 *
 *  Created on: 14. nov. 2015
 *      Author: Lima
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "em_gpio.h"
#include "em_cmu.h"

typedef enum
{
	ZOOM_IN 	= 12,
	ZOOM_OUT 	= 13,
	JOY_UP 		= 2,
	JOY_DOWN 	= 0,
	JOY_LEFT 	= 1,
	JOY_RIGTH 	= 4,
	ZOOM_CENTER = 3
} Button_TypeDef;

typedef enum
{
	PORT_GPIO		= gpioPortA,
	PORT_JOYSTICK	= gpioPortC,
	PORT_DONE		= gpioPortC,
	PORT_SPI		= gpioPortD,
	PORT_INIT_B		= gpioPortD,
	PORT_ZOOM		= gpioPortD

} Port_TypeDef;

typedef enum
{
	SIG_GPIO0		= 7,
	SIG_GPIO1		= 8,
	SIG_GPIO2		= 9,
	SIG_GPIO3		= 10,
	SIG_GPIO4		= 11,

	SIG_DONE		= 10,
	SIG_INIT_B		= 8

} Sig_TypeDef;

extern void buttons_init();


#endif /* BUTTONS_H_ */
