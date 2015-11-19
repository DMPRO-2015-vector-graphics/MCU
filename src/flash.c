/*
 * flash.c
 *
 *  Created on: 18. nov. 2015
 *      Author: Lima
 */

#include "flash.h"
#include "em_usart.h"

const int CS_pin = 3;
const GPIO_Port_TypeDef SPI_port = gpioPortD;
USART_InitSync_TypeDef USART_SPI;

extern void flash_init()
{
//	/* Enable clock for USART1 */
//	CMU_ClockEnable(cmuClock_USART1, true);
//	/* Custom initialization for USART1 */
//
//	USART_SPI.baudrate     = 4000000;
//	USART_SPI.databits     = usartDatabits8;
//	USART_SPI.msbf         = 1;
//	USART_SPI.master       = 1;
//	USART_SPI.clockMode    = usartClockMode0;
//	USART_SPI.prsRxEnable  = 0;
//	USART_SPI.autoTx       = 0;
//
//
//	USART_InitSync(USART1, &USART_SPI);
//
//	  /* Module USART1 is configured to location 1 */
//	  USART1->ROUTE = (USART1->ROUTE & ~_USART_ROUTE_LOCATION_MASK) | USART_ROUTE_LOCATION_LOC1;
//	  /* Enable signals TX, RX, CLK */
//	  USART1->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_CLKPEN;

	GPIO_PinModeSet(gpioPortD, 0, gpioModePushPull, 1);
	GPIO_PinModeSet(gpioPortD, 1, gpioModeInputPull, 1);
	GPIO_PinModeSet(gpioPortD, 2, gpioModePushPull, 0);
	GPIO_PinModeSet(gpioPortD, 3, gpioModePushPull, 1);

}

extern uint8_t getID()
{

	GPIO_PinOutClear(SPI_port, CS_pin);
	uint8_t res = USART_SpiTransfer(&USART_SPI,0x90);
	GPIO_PinOutSet(SPI_port, CS_pin);
	return res;
}
