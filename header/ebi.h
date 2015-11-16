/*
 * ebi.h
 *
 *  Created on: 14. nov. 2015
 *      Author: Lima
 */

#ifndef EBI_H_
#define EBI_H_

#include "em_ebi.h"
#include "em_cmu.h"
#include "em_gpio.h"

#include <stdint.h>

#define BANK0_BASE_ADDR 0x80000000
#define BANK1_BASE_ADDR 0x84000000

extern void ebi_init();
extern void ebi_write(int address, uint16_t value);
extern uint16_t ebi_read(int address);

#endif /* EBI_H_ */
