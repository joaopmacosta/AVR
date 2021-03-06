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
#include "../../TC_driver/TC_driver.h"

// AVR headers.
#include <avr/io.h>

#ifndef BOARD_INIT_H_INCLUDED_
#define BOARD_INIT_H_INCLUDED_

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
  //* TIMER E0                                                            *
  //***********************************************************************
  
  // Setting the period/TOP of timer E1
  // F_CPU/prescaler * period - 1 = ticks
  // 32000000/256 * 0.001s - 1 = 125
  TC_SetPeriod(&TCE0, 125); //TE0C->PER = 125

  // Setting the clock of timer E0 (F_CPU/256)
  TC0_ConfigClockSource(&TCE0, TC_CLKSEL_DIV256_gc); //tc->CTRLA[3:0] = xxx

  // Setting timer E0 to the normal operating mode
  TC0_ConfigWGM(&TCE0, TC_WGMODE_NORMAL_gc); //Normal Mode: TOP = PER, OVF = TOP

  // Enabling low-priority overflow interruptions
  TC0_SetOverflowIntLevel(&TCE0, TC_OVFINTLVL_LO_gc);

  //***********************************************************************
  //* GPIO.                                                               *
  //***********************************************************************

  // Setup pins as IN/OUTputs
  GPIO_CFG_OUT(LED, false);
  //GPIO_CFG_OPC(LED, GPIO_OPC_PULLDOWN);

  //***********************************************************************
  //* Interrupt levels.                                                   *
  //***********************************************************************
  //Enables High, Medium and Low Level Interrupts
  PMIC.CTRL |= PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
}

#endif /* BOARD_INIT_H_INCLUDED_ */
