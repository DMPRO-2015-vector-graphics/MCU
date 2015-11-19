/*
 * flash.h
 *
 *  Created on: 18. nov. 2015
 *      Author: Lima
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "em_usart.h"
#include "em_cmu.h"
#include "em_gpio.h"

extern void flash_init();

extern uint8_t getID();

#endif /* FLASH_H_ */
