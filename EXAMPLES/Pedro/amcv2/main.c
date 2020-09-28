//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: Pedro Gonçalves                                                  *
//***************************************************************************

// ISO C99 headers.
#include <stdbool.h>

// AVR headers.
#include <util/atomic.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

// Local headers.
#include "wdt/wdt.h"
#include "drivers/uart.h"
#include "drivers/io.h"
#include "board_init.h"
#include "config.h"
#include "motor_parser.h"
#include "cpu_parser.h"

int cnt_TE0_update_state = 0;
int reset_cnt = 0;

int
main(void)
{ 
  cli();
  wdt_enable(WDT_PERIOD);

  board_init();
  initUsart();
  init_motor_parser();
  init_cpu_parser();

  sei();

  _delay_ms(100);

#if 0
  UART_sendString(DEBUG, "\r\r  AMCV2 >>> Hello ...\r\r");
#endif

  while (true)
  {
    wdt_reset();
    _delay_ms(1);
  }

  return 0;
}

ISR(TCE0_OVF_vect)
{
  if(cnt_TE0_update_state >= 31)
  {
    cnt_TE0_update_state = -1;
    //gpio_tgl_np(&LED_DEBUG_PORT, LED_DEBUG_PIN);
    if(reset_cnt > TIME_TO_REFRESH_IS_ALIVE)
    {
      gpio_clr_np(&LED_MOTOR_0_PORT, LED_MOTOR_0_PIN);
      gpio_clr_np(&LED_MOTOR_1_PORT, LED_MOTOR_1_PIN);
      gpio_clr_np(&LED_MOTOR_2_PORT, LED_MOTOR_2_PIN);
      gpio_clr_np(&LED_MOTOR_3_PORT, LED_MOTOR_3_PIN);
      reset_cnt = 0;
    }
    reset_cnt++;
    //gpio_tgl_np(&LED_MOTOR_3_PORT, LED_MOTOR_3_PIN);
  }

  cnt_TE0_update_state++;
}