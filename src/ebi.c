/*
 * ebi.c
 *
 *  Created on: 14. nov. 2015
 *      Author: Lima
 */

#include "ebi.h"

extern void ebi_init()
{
	EBI_Init_TypeDef ebiConfig = EBI_INIT_DEFAULT;

	CMU_ClockEnable(cmuClock_EBI, true);
	CMU_ClockEnable(cmuClock_GPIO, true);


	/* --- Configure GPIO pins as push pull -------------------- */

	    /* EBI AD9..15 */
	    GPIO_PinModeSet( gpioPortA,  0, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortA,  1, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortA,  2, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortA,  3, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortA,  4, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortA,  5, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortA,  6, gpioModePushPull, 0 );

	    /* EBI AD8 */
	    GPIO_PinModeSet( gpioPortA, 15, gpioModePushPull, 0 );

	    /* EBI A00-A06 */
	    GPIO_PinModeSet( gpioPortA, 12, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortA, 13, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortA, 14, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortB,  9, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortB, 10, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortC,  6, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortC,  7, gpioModePushPull, 0 );

	    /* EBI A07-A14 */
	    GPIO_PinModeSet( gpioPortE,  0, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortE,  1, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortC,  9, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortC,  10, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortE,  4, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortE,  5, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortE,  6, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortE,  7, gpioModePushPull, 0 );

	    /* EBI A15-A18 */
	    GPIO_PinModeSet( gpioPortC,  8, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortB,  0, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortB,  1, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortB,  2, gpioModePushPull, 0 );

	    /* EBI CS0-CS3 */
	    GPIO_PinModeSet( gpioPortD,  9, gpioModePushPull, 1 );
	    GPIO_PinModeSet( gpioPortD, 11, gpioModePushPull, 1 );
	    GPIO_PinModeSet( gpioPortD, 12, gpioModePushPull, 1 );

	    /* EBI AD0..7 */
	    GPIO_PinModeSet( gpioPortE,  8, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortE,  9, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortE, 10, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortE, 11, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortE, 12, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortE, 13, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortE, 14, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortE, 15, gpioModePushPull, 0 );

	    /* EBI ARDY/WEN/REN/ALE */
	    GPIO_PinModeSet( gpioPortF,  2, gpioModeInput,    0 );
	    GPIO_PinModeSet( gpioPortF,  8, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortF,  9, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortC, 11, gpioModePushPull, 0 );

	    /* EBI Byte Lane 0 support BL0/BL1 */
	    GPIO_PinModeSet( gpioPortF, 6, gpioModePushPull, 0 );
	    GPIO_PinModeSet( gpioPortF, 7, gpioModePushPull, 0 );


	    /* --------------------------------------------------------- */
	    /* SRAM, Bank 0, Base Address 0x80000000  */
	    /* --------------------------------------------------------- */
	    ebiConfig.banks       = EBI_BANK0;
	    ebiConfig.csLines     = EBI_CS0;
	    ebiConfig.mode        = ebiModeD16;
	    ebiConfig.alePolarity = ebiActiveHigh;
	    ebiConfig.location    = ebiLocation1;
	    /* keep blEnable */
	    ebiConfig.blEnable     = false;
	    ebiConfig.addrHalfALE  = false;
	    ebiConfig.readPrefetch = false;
	    ebiConfig.noIdle       = true;

	    /* keep alow/ahigh configuration */
	    ebiConfig.aLow = ebiALowA0;
	    ebiConfig.aHigh = ebiAHighA19;

	    /* set polarity to active low */
	    ebiConfig.wePolarity = ebiActiveLow;
	    ebiConfig.rePolarity = ebiActiveLow;

	    /* Address Setup and hold time */
	    ebiConfig.addrHoldCycles  = 3;
	    ebiConfig.addrSetupCycles = 3;


	    /* Read cycle times */
	    ebiConfig.readStrobeCycles = 7;
	    ebiConfig.readHoldCycles   = 3;
	    ebiConfig.readSetupCycles  = 3;

	    /* Write cycle times */
	    ebiConfig.writeStrobeCycles = 7;
	    ebiConfig.writeHoldCycles   = 3;
	    ebiConfig.writeSetupCycles  = 3;

	    /* Configure EBI bank 0 */
	    EBI_Init(&ebiConfig);

}

extern void ebi_write(int address, volatile uint16_t value)
{
	*(uint16_t *)(BANK0_BASE_ADDR + (address << 1)) = value;
}

extern uint16_t ebi_read(int address)
{
	return *(volatile uint16_t*)(BANK0_BASE_ADDR + (address << 1));
}

extern void ebi_disable()
{
	EBI_Disable();

}
