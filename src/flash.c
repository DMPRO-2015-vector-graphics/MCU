/*
 * flash.c
 *
 *  Created on: 18. nov. 2015
 *      Author: Lima
 */

#include "flash.h"
#include "em_usart.h"
#include "buttons.h"

const int CS_pin = 3;
const GPIO_Port_TypeDef SPI_port = gpioPortD;

USART_InitSync_TypeDef USART_SPI;

void USART1_setup(void)
{
  USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;

  init.baudrate     = 1000000;	/* 1Mbit/s */
  init.databits     = usartDatabits8;/* 8 databit transmission */
  init.msbf         = 1;	/* Send MSB last */
  init.master       = 1;	/* master mode */
  init.clockMode    = usartClockMode0;	/* Clock idle low, sample on rising edge */
  init.prsRxEnable  = 0;	/* PRS Channel 0 */
  init.autoTx       = 0;	/* No AUTOTX mode */

  USART_InitSync(USART1, &init);
}

extern void flash_init()
{
	 /* configure Pin D0 (TX) as input */
	  GPIO_PinModeSet(PORT_SPI, 0, gpioModePushPull, 0);
	  /* Configure PIN D1 (RX) as output */
	  GPIO_PinModeSet(PORT_SPI, 1, gpioModeInput, 0);
	  /* configure PIN D2 (CLK) as output */
	  GPIO_PinModeSet(PORT_SPI, 2, gpioModePushPull, 0);
	  /* configure Pin D3 (CS) as output */
	  GPIO_PinModeSet(PORT_SPI, 3, gpioModePushPull, 0);

	  /* To avoid false start, configure output US1_CS as high on PC14 */
	  //GPIO_PinOutClear(PORT_SPI, 3);

	  /* Enable clock for USART1 */
	  CMU_ClockEnable(cmuClock_USART1, true);
	  /* Custom initialization for USART1 */
	  USART1_setup();
	  /* Module USART1 is configured to location 1 */
	  USART1->ROUTE = (USART1->ROUTE & ~_USART_ROUTE_LOCATION_MASK) | USART_ROUTE_LOCATION_LOC1;
	  /* Enable signals TX, RX, CLK, CS */
	  USART1->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_CLKPEN | USART_ROUTE_CSPEN;

	  USART_IntClear(USART1, USART_IF_RXDATAV);
	  NVIC_ClearPendingIRQ(USART1_RX_IRQn);

}

extern uint8_t getID()
{

	GPIO_PinOutClear(PORT_SPI, 3);
	uint8_t res = USART_SpiTransfer(USART1,0x90);
	GPIO_PinOutSet(PORT_SPI, 3);
	return res;
}
