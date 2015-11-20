/*
 * buttons.c
 *
 *  Created on: 14. nov. 2015
 *      Author: Lima
 */

#include "buttons.h"
#include "ebi.h"

extern void buttons_init()
{
	/* Enable clock for GPIO module */
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Configure GPIO Harness */
	GPIO_PinModeSet(gpioPortA, 7, gpioModePushPull, 0);
	GPIO_PinModeSet(gpioPortA, 8, gpioModePushPull, 0);
	GPIO_PinModeSet(gpioPortA, 9, gpioModePushPull, 0);
	GPIO_PinModeSet(gpioPortA, 10, gpioModePushPull, 0);
	GPIO_PinModeSet(gpioPortA, 11, gpioModePushPull, 0);

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

	/* Configure Done Signal */
	GPIO_PinModeSet(PORT_DONE, SIG_DONE, gpioModeInput, 1);

	/* Enable GPIO_ODD interrupt vector in NVIC */
	NVIC_EnableIRQ(GPIO_ODD_IRQn);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);

	/* Configure Zoom buttons interrupt on falling edge */
	GPIO_IntConfig(gpioPortD, 12, true, true, true);
	GPIO_IntConfig(gpioPortD, 13, true, true, true);
	/* Configure Joy buttons interrupt on rising edge */
	GPIO_IntConfig(gpioPortC, 0, true, false, true);
	GPIO_IntConfig(gpioPortC, 1, true, false, true);
	GPIO_IntConfig(gpioPortC, 2, true, false, true);
	GPIO_IntConfig(gpioPortC, 3, true, false, true);
	GPIO_IntConfig(gpioPortC, 4, true, false, true);
	/* Configure Done sig */
	GPIO_IntConfig(PORT_DONE, SIG_DONE, true, true, true);
}

void interrupt_handler(uint32_t flag) {

	//Zoom Out
	if (GPIO_PinInGet(PORT_ZOOM, ZOOM_OUT) == 0) {
		GPIO_PinOutSet(PORT_GPIO, SIG_GPIO0);
		//on_button_press(ZOOM_OUT);
	}else
	{
		GPIO_PinOutClear(PORT_GPIO, SIG_GPIO0);
	}
	//Zoom In
	if (GPIO_PinInGet(gpioPortD, 13) == 0) {
		//on_button_press(ZOOM_IN);
	}
	//Joy Down
	if (GPIO_PinInGet(gpioPortC, 0) == 1) {
		GPIO_PinOutToggle(gpioPortA, 9);
	}
	//Joy Left
	if (GPIO_PinInGet(gpioPortC, 1) == 1) {
		GPIO_PinOutToggle(gpioPortA, 10);
	}
	//Joy Up
	if (GPIO_PinInGet(gpioPortC, 2) == 1) {
		GPIO_PinOutToggle(gpioPortA, 11);
	}
	//Joy Pressed
	if (GPIO_PinInGet(gpioPortC, 3) == 1) {
		GPIO_PinOutToggle(gpioPortA, 11);
	}
	//Joy Right
	if (GPIO_PinInGet(gpioPortC, 4) == 1) {
		GPIO_PinOutToggle(gpioPortA, 11);
	}

	if( GPIO_PinInGet(PORT_DONE, SIG_DONE) == 0){
		GPIO_PinOutSet(PORT_GPIO, SIG_GPIO4);
	}else{
		GPIO_PinOutClear(PORT_GPIO, SIG_GPIO4);
	}
}

void GPIO_ODD_IRQHandler(void) {
	/* clear flag for PE1 interrupt */
	uint32_t flag = GPIO_IntGet();
	interrupt_handler(flag);
	GPIO_IntClear(flag);
}

void GPIO_EVEN_IRQHandler(void) {
	/* clear flag for PE1 interrupt */
	uint32_t flag = GPIO_IntGet();
	interrupt_handler(flag);
	GPIO_IntClear(flag);
}

void GPIO_EFM_Clear()
{
	GPIO_PinOutClear(gpioPortA, 7);
	GPIO_PinOutClear(gpioPortA, 8);
	GPIO_PinOutClear(gpioPortA, 9);
	GPIO_PinOutClear(gpioPortA, 10);
	GPIO_PinOutClear(gpioPortA, 11);
}

void GPIO_Harness_Set(uint8_t data)
{
	for(int i = 0; i < 6 ; i++)
	{

	}
}
