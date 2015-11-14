/*
 * buttons.c
 *
 *  Created on: 14. nov. 2015
 *      Author: Lima
 */

#include "buttons.h"

extern void buttons_init()
{
	/* Enable clock for GPIO module */
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Configure GPIO Harness */
	GPIO_PinModeSet(gpioPortA, 7, gpioModePushPull, 1);
	GPIO_PinModeSet(gpioPortA, 8, gpioModePushPull, 1);
	GPIO_PinModeSet(gpioPortA, 9, gpioModePushPull, 1);
	GPIO_PinModeSet(gpioPortA, 10, gpioModePushPull, 1);
	GPIO_PinModeSet(gpioPortA, 11, gpioModePushPull, 1);

	/* Configure Zoom buttons as input with filter enable */
	GPIO_PinModeSet(gpioPortD, 12, gpioModeInputPullFilter, 1);
	GPIO_PinModeSet(gpioPortD, 13, gpioModeInputPullFilter, 1);

	/* Configure Joystick  as input with filter enable */
	GPIO_PinModeSet(gpioPortC, 0, gpioModeInputPullFilter, 0);
	GPIO_PinModeSet(gpioPortC, 1, gpioModeInputPullFilter, 0);
	GPIO_PinModeSet(gpioPortC, 2, gpioModeInputPullFilter, 0);
	GPIO_PinModeSet(gpioPortC, 3, gpioModeInputPullFilter, 0);
	GPIO_PinModeSet(gpioPortC, 4, gpioModeInputPullFilter, 0);
	GPIO_PinModeSet(gpioPortC, 5, gpioModePushPull, 1);

	/* Enable GPIO_ODD interrupt vector in NVIC */
	NVIC_EnableIRQ(GPIO_ODD_IRQn);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);

	/* Configure Zoom buttons interrupt on falling edge */
	GPIO_IntConfig(gpioPortD, 12, false, true, true);
	GPIO_IntConfig(gpioPortD, 13, false, true, true);
	/* Configure Zoom buttons interrupt on rising edge */
	GPIO_IntConfig(gpioPortC, 0, true, false, true);
	GPIO_IntConfig(gpioPortC, 1, true, false, true);
	GPIO_IntConfig(gpioPortC, 2, true, false, true);
	GPIO_IntConfig(gpioPortC, 3, true, false, true);
	GPIO_IntConfig(gpioPortC, 4, true, false, true);
}

void interrupt_handler() {

	//Zoom In
	if (GPIO_PinInGet(gpioPortD, 12) == 0) {
		GPIO_PinOutToggle(gpioPortA, 7);
	}
	//Zoom Out
	else if (GPIO_PinInGet(gpioPortD, 13) == 0) {
		GPIO_PinOutToggle(gpioPortA, 8);
	}
	//Joy Down
	else if (GPIO_PinInGet(gpioPortC, 0) == 1) {
		GPIO_PinOutToggle(gpioPortA, 9);
	}
	//Joy Left
	else if (GPIO_PinInGet(gpioPortC, 1) == 1) {
		GPIO_PinOutToggle(gpioPortA, 10);
	}
	//Joy Up
	else if (GPIO_PinInGet(gpioPortC, 2) == 1) {
		GPIO_PinOutToggle(gpioPortA, 11);
	}
	//Joy Pressed
	else if (GPIO_PinInGet(gpioPortC, 3) == 1) {
		GPIO_PinOutToggle(gpioPortA, 11);
	}
	//Joy Right
	else if (GPIO_PinInGet(gpioPortC, 4) == 1) {
		GPIO_PinOutToggle(gpioPortA, 11);
	}
}

void GPIO_ODD_IRQHandler(void) {
  /* clear flag for PE1 interrupt */
  GPIO_IntClear(0xff);
  interrupt_handler();
}

void GPIO_EVEN_IRQHandler(void) {
  /* clear flag for PE1 interrupt */
  GPIO_IntClear(0xff);
  interrupt_handler();
}
