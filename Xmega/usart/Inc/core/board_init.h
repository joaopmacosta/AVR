//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: Pedro Gonçalves                                                  *
//***************************************************************************

/// ISO C 99 headers.
#include <stddef.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Local Headers
#include "../../config.h"
#include "../driver/io.h"
#include "../../Inc/driver/usart_driver.h"
#include "../../TC_driver/TC_driver.h"

// AVR headers.
#include <avr/io.h>

#ifndef BOARD_INIT_H_INCLUDED_
#define BOARD_INIT_H_INCLUDED_

/*! Define that selects the Usart used in example. */
#define USART USARTC0
/*! USART data struct used in example. */
USART_data_t USART_data;

static inline void
board_init(void)
{
  //***********************************************************************
  // System Clock.                                                        *
  //***********************************************************************
  // ENABLE INTERNAL 32MHZ OSCILLATOR

  CCP = CCP_IOREG_gc;

  OSC.CTRL = OSC_RC32MEN_bm;

  while (!(OSC.STATUS & OSC_RC32MRDY_bm))
    ;

  CCP = CCP_IOREG_gc;

  CLK.CTRL = CLK_SCLKSEL_RC32M_gc;

  //***********************************************************************
  //* GPIO.                                                               *
  //***********************************************************************

  // Setup pins as IN/OUTputs
  GPIO_CFG_OUT(LED, true);

  // SERIAL INTERFACE
  /* This PORT setting is only valid to USARTC0 if other USARTs is used a
	 * different PORT and/or pins are used. */
  /* PC3 (TXD0) as output. */
  PORTC.DIRSET = PIN3_bm;
  /* PC2 (RXD0) as input. */
  PORTC.DIRCLR = PIN2_bm;

  /* Use USARTC0 and initialize buffers. */
  USART_InterruptDriver_Initialize(&USART_data, &USART, USART_DREINTLVL_LO_gc);

  /* USARTC0, 8 Data bits, No Parity, 1 Stop bit. */
  USART_Format_Set(USART_data.usart, USART_CHSIZE_8BIT_gc,
                   USART_PMODE_DISABLED_gc, false);

  /* Enable RXC interrupt. */
  USART_RxdInterruptLevel_Set(USART_data.usart, USART_RXCINTLVL_HI_gc);

  /* Set Baudrate to 9600 bps:
	 * Use the default I/O clock frequency that is 2 MHz.
	 * Do not use the baudrate scale factor
	 *
	 * Baudrate select = (1/(16*(((I/O clock frequency)/Baudrate)-1)
	 *                 = 12
	 */
  USART_Baudrate_Set(&USART, 12, 0);

  /* Enable both RX and TX. */
  USART_Rx_Enable(USART_data.usart);
  USART_Tx_Enable(USART_data.usart);

  //***********************************************************************
  //* Interrupt levels.                                                   *
  //***********************************************************************
  //Enables High, Medium and Low Level Interrupts
  PMIC.CTRL |= PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
}

#endif /* BOARD_INIT_H_INCLUDED_ */
