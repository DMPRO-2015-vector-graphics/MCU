/**************************************************************************//**
 * @file
 * @brief Empty Project
 * @author Energy Micro AS
 * @version 3.20.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs Software License Agreement. See 
 * "http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt"  
 * for details. Before using this software for any purpose, you must agree to the 
 * terms of that agreement.
 *
 ******************************************************************************/
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"

#include "ebi.h"
#include "program.h"
#include "buttons.h"
#include "flash.h"

//#define DEBUG

void write_program();


uint32_t msTicks;

void SysTick_Handler(void)
{
  /* Increment counter necessary in Delay()*/
  msTicks++;
}

void Delay(uint32_t dlyTicks)
{
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) ;
}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{

  /* Chip errata */
  CHIP_Init();

  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);

  /* Setup SysTick Timer for 1 msec interrupts  */
  //if (SysTick_Config(CMU_ClockFreqGet(cmuClock_HF) / 1000)) while (1) ;

  ebi_init();

  buttons_init();

  flash_init();

  write_program();

  //uint8_t id = getID();

//#ifdef DEBUG
//  uint16_t result0 = ebi_read(0x0000);
//  uint16_t result90 = ebi_read(0x0000);
//  uint16_t result1 = ebi_read(0x0001);
//  uint16_t result2 = ebi_read(0x0002);
//  uint16_t result3 = ebi_read(0x0003);
//  uint16_t result4 = ebi_read(0x0004);
//  uint16_t result5 = ebi_read(0x0005);
//  uint16_t result6 = ebi_read(0x0006);
//#endif //DEBUG


  /* Infinite loop */
  while (1) {
	  //EMU_EnterEM2();
  }
}

void write_program()
{

	  uint16_t program_data[] = {
	  		0x0820, 0x1111,
	  		0x345F, 0xFFFF,
	  		0x385F, 0xFFFF,
	  		0x1401, 0x1000,
	  		0x2C00, 0x0000,
	  		0x0400, 0x0014
	  };

	//GPIO_PinModeSet(PORT_DONE, SIG_DONE, gpioModeInput, 1 );
	GPIO_PinModeSet( gpioPortD, 10, gpioModePushPull, 1 );

	/* wait for FPGA to be flashed, before writing to SRAM */
	while(GPIO_PinInGet(PORT_DONE, SIG_DONE) == 1);

	// Clear CS1 to give control to EFM
	GPIO_PinOutClear(gpioPortD, 10);

	for(uint16_t i = 0; i < size; i++)
	{
		ebi_write(i, program_data[i]);

	}


	ebi_disable();

	GPIO_PinModeSet( gpioPortD,  9, gpioModePushPull, 0);
	GPIO_PinOutClear(gpioPortD, 9);

	//Set CS1 to give control to FPGA
	GPIO_PinOutSet(gpioPortD, 10);
	//Set CS0 low to allow FPGA to read SRAM
	GPIO_PinOutClear(gpioPortD, 9);
}

void on_button_press(Button_TypeDef btn)
{
//	switch(btn)
//	{
//	case(ZOOM_IN):
//		GPIO_PinOutSet(gpioPortA, 7);
//		int i = 0; while(i < 100000) i++;
//		GPIO_PinOutClear(gpioPortA, 7);
//		break;
//	default:
//		break;
//	}
}
