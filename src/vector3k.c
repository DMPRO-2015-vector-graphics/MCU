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
//#include "em_ebi.h"

#include "ebi.h"
#include "program.h"
#include "buttons.h"

void write_program();


/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Chip errata */
  CHIP_Init();

  ebi_init();

  buttons_init();

  write_program();

//
//  ebi_write(0x0,0b10101);
//  ebi_write(0x1,0b11100);
//
//  ebi_write(0x10, 0xff00);
//
//  uint16_t result = ebi_read(0x0000);
//  uint16_t result1 = ebi_read(0x0001);
//  uint16_t result2 = ebi_read(0x0002);
//  uint16_t result3 = ebi_read(0x0003);
//  int addr;
//
//  if (result == 3){
//	  addr = 0xff00;
//  }else{
//	  addr = 0x00ff;
//  }



  /* Infinite loop */
  while (1) {

  }
}

void write_program()
{
	for(uint16_t i = 0; i < size; i++)
	{
		ebi_write(i, program_data[i]);
	}

	// Set CS1 to give control to FPGA
	GPIO_PinModeSet( gpioPortD, 10, gpioModePushPull, 1 );
	GPIO_PinOutSet(gpioPortD, 10);
}
