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
#include "../../Inc/driver/servo_driver.h"
#include "../../TC_driver/TC_driver.h"

// AVR headers.
#include <avr/io.h>

#ifndef BOARD_INIT_H_INCLUDED_
#define BOARD_INIT_H_INCLUDED_

extern servo_motor_t motor_disc;

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
  GPIO_CFG_OPC(LED, GPIO_OPC_PULLDOWN);

  SERVO_CFG_BRAKE(motor_disc, MOTOR_RUNBRAKE, true);
  SERVO_CFG_START(motor_disc, MOTOR_STARTSTOP, true);

  //***********************************************************************
  //* GPIO/External Interrupt                                             *
  //***********************************************************************
  // External interrupt 0 on PC1, enable pullup, sence falling edge
  //PORTC.PIN0CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_FALLING_gc;
  //PORTC.INT0MASK = (1 << BUTTON_PIN);
  //PORTC.INTCTRL = PORT_INT0LVL_MED_gc;

  //***********************************************************************
  //* Interrupt levels.                                                   *
  //***********************************************************************
  //Enables High, Medium and Low Level Interrupts
  PMIC.CTRL |= PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
}

#endif /* BOARD_INIT_H_INCLUDED_ */
