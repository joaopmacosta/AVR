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

// Board configuration.
#include "config.h"

// AVR headers.
#include <avr/io.h>

#include "drivers/io.h"
#include "TC/TC_driver.h"

#ifndef BOARD_INIT_H_INCLUDED_
#define BOARD_INIT_H_INCLUDED_

static inline void
board_init(void)
{
  //***********************************************************************
  // System Clock.                                                        *
  //***********************************************************************

  // ========= System Clock configuration =========
  // Set to external 16Mhz crystal, using the PLL at *2
  // set it to be a 12-16Mhz crystal with a slow start-up time.
  OSC.XOSCCTRL = OSC_FRQRANGE_12TO16_gc | OSC_XOSCSEL_XTAL_16KCLK_gc ;
  OSC.CTRL |= OSC_XOSCEN_bm ; // enable it
  while( (OSC.STATUS & OSC_XOSCRDY_bm) == 0 ){} // wait until it's stable

  // The external crystal is now running and stable.
  // (Note that it's not yet selected as the clock source)
  // Now configure the PLL to be eXternal oscillator * 2
  OSC.PLLCTRL = OSC_PLLSRC_XOSC_gc | 2 ;

  // now enable the PLL...
  OSC.CTRL |= OSC_PLLEN_bm ; // enable the PLL...
  while( (OSC.STATUS & OSC_PLLRDY_bm) == 0 ){} // wait until it's stable

  // And now, *finally*, we can switch from the internal 2Mhz clock to the PLL
  CCP = CCP_IOREG_gc;	// protected write follows
  CLK.CTRL = CLK_SCLKSEL_PLL_gc;	// The System clock is now  PLL (16Mhz * 2)

  //***********************************************************************
  //* TIMER E0                                                            *
  //***********************************************************************

  // Setting the period of timer E1
  // F_CPU/1024/[aeg] - 1 = periood
  // 32000000 / 1024 / 50 - 1  (60 = 519), (50 = 624)
  TC_SetPeriod(&TCE0, 519);
 
  // Setting the clock of timer E0 (F_CPU/1024)
  TC0_ConfigClockSource(&TCE0, TC_CLKSEL_DIV1024_gc);
  // Setting timer E0 to the normal operating mode
  TC0_ConfigWGM(&TCE0, TC_WGMODE_NORMAL_gc);
 
  // Enabling low-priority overflow interruptions
  TC0_SetOverflowIntLevel(&TCE0,TC_OVFINTLVL_LO_gc);

  //***********************************************************************
  //* UART0.                                                              *
  //***********************************************************************

  GPIO_CFG_OUT(UART0_TX, false);
  GPIO_CFG_IN(UART0_RX);

  //***********************************************************************
  //* UART1.                                                              *
  //***********************************************************************

  GPIO_CFG_OUT(UART1_TX, false);
  GPIO_CFG_IN(UART1_RX);

  //***********************************************************************
  //* UART2.                                                              *
  //***********************************************************************

  GPIO_CFG_OUT(UART2_TX, false);
  GPIO_CFG_IN(UART2_RX);

  //***********************************************************************
  //* UART3.                                                              *
  //***********************************************************************

  GPIO_CFG_OUT(UART3_TX, false);
  GPIO_CFG_IN(UART3_RX);

  //***********************************************************************
  //* UART4.                                                              *
  //***********************************************************************

  GPIO_CFG_OUT(UART4_TX, false);
  GPIO_CFG_IN(UART4_RX);

  //***********************************************************************
  //* GPIO.                                                               *
  //***********************************************************************

  // Setup chip select pin.
  GPIO_CFG_OUT(LED_DEBUG, true);
  GPIO_CFG_OUT(LED_MOTOR_0, false);
  GPIO_CFG_OUT(LED_MOTOR_1, false);
  GPIO_CFG_OUT(LED_MOTOR_2, false);
  GPIO_CFG_OUT(LED_MOTOR_3, false);

  //***********************************************************************
  //* Interrupt levels.                                                   *
  //***********************************************************************
  
  PMIC.CTRL |= PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm;

}

#endif /* BOARD_INIT_H_ */