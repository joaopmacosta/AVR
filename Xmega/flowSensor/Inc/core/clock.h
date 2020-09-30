//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: João Costa                                                       *
//***************************************************************************

#ifndef CLOCK_H_INCLUDED_
#define CLOCK_H_INCLUDED_

/// ISO C 99 headers.
#include <stddef.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Local Headers
#include "../../config.h"
#include "../../TC_driver/TC_driver.h"

// AVR headers.
#include <avr/io.h>


static inline void
clock_init(void)
{
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
}

uint16_t T0_millis = 0;
//uint8_t over=0;
ISR(TCE0_OVF_vect)
{
  T0_millis++;
  //GPIO_TGL(LED);
}

#endif //CLOCK_H_INCLUDED_