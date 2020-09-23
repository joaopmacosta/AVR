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

extern USART_data_t USART_cpu;

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
  GPIO_CFG_OUT(LED, false);

  GPIO_CFG_IN(UART0_RX);
  GPIO_CFG_OUT(UART0_TX, false);

  //***********************************************************************
  //* SERIAL                                                              *
  //***********************************************************************
  // Use USARTC0 and initialize buffers.
  USART_InterruptDriver_Initialize(&USART_cpu, &USART_CPU, USART0_DRE_INT_LVL);

  // USARTC0, 8 Data bits, No Parity, 1 Stop bit.
  USART_Format_Set(USART_cpu.usart, USART0_DATA_BITS,
                   USART0_PARITY_MODE, false);

  // Set Baudrate to 9600 bps:
  // Baudrate select = (1/(16*(((I/O clock frequency)/Baudrate)-1) = 12
  USART_Baudrate_Set(&USART_CPU, 12, 0);

  // Enable RXC interrupt.
  USART_RxdInterruptLevel_Set(USART_cpu.usart, USART0_RX_INT_LVL);

  // Enable both RX and TX.
  USART_Rx_Enable(USART_cpu.usart);
  USART_Tx_Enable(USART_cpu.usart);

  //***********************************************************************
  //* Interrupt levels.                                                   *
  //***********************************************************************
  //Enables High, Medium and Low Level Interrupts
  PMIC.CTRL |= PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
}

#endif /* BOARD_INIT_H_INCLUDED_ */
