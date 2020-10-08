//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: João Costa                                                       *
//***************************************************************************

#ifndef BOARD_INIT_H_INCLUDED_
#define BOARD_INIT_H_INCLUDED_

/// ISO C 99 headers.
#include <stddef.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Local Headers
#include "../../config.h"
#include "../driver/io.h"
//#include "../driver/usart.h"
#include "../../TC_driver/TC_driver.h"

// AVR headers.
#include <avr/io.h>

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

  GPIO_CFG_IN(FLOW_SENSOR);
  GPIO_CFG_OPC(FLOW_SENSOR, GPIO_OPC_PULLDOWN);
  GPIO_CFG_ISC(FLOW_SENSOR, GPIO_ISC_RISING);

  GPIO_CFG_OUT(UART0_TX, false);
  GPIO_CFG_IN(UART0_RX);

  //***********************************************************************
  //* GPIO/External Interrupt                                             *
  //***********************************************************************
  // External interrupt 0 on PC1, enable pullup, sence falling edge
  //PORTC.PIN0CTRL = PORT_OPC_PULLDOWN_gc | PORT_ISC_RISING_gc;
  PORTD.INT0MASK = (1 << FLOW_SENSOR_PIN);
  PORTD.INTCTRL = PORT_INT0LVL_MED_gc;

  //***********************************************************************
  //* Interrupt levels.                                                   *
  //***********************************************************************
  //Enables High, Medium and Low Level Interrupts
  PMIC.CTRL |= PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;
}

#endif /* BOARD_INIT_H_INCLUDED_ */
