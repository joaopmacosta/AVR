//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: Pedro Gonçalves                                                  *
//***************************************************************************

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include "../../Inc/driver/uart.h"
#include "../../Inc/driver/io.h"
#include "../../config.h"

//#include "../motor_parser.h"
//#include "../cpu_parser.h"

int cnt_reset_stop_emerg = 0;
char *text_emerg = "$S,0*";

void initUsart(void)
{
  //DEBUG
  USARTD0_BAUDCTRLB = UART0_BAUDCTRLB;
  USARTD0_BAUDCTRLA = UART0_BAUDCTRLA;
  USARTD0_CTRLA = UART0_CTRLA;
  USARTD0_CTRLB = UART0_CTRLB;
  USARTD0_CTRLC = UART0_CTRLC;
}

void UART_sendChar(uint8_t usart, uint8_t data)
{
  switch (usart)
  {
  case DEBUG:
    while (!(USARTD0_STATUS & USART_DREIF_bm))
      ;
    USARTD0_DATA = data;
    break;

  default:
    break;
  }
}

void UART_sendString(uint8_t usart, char *str)
{
  register char c;
  while ((c = *str++))
    UART_sendChar(usart, c);
}

void UART_sendInt(uint8_t usart, int value)
{
  char string[17];
  UART_sendString(usart, itoa(value, string, 10)); // base 10
}

void UART_sendLint(uint8_t usart, long int data)
{
  char buf[33];
  UART_sendString(usart, ltoa(data, buf, 10));
}

//DEBUG
ISR(DEBUG_RX_IVEC)
{
  //cpu_praser(USARTD0_DATA);
  cnt_reset_stop_emerg = 0;
}

char debug_bfr[256];

void
spew(const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);

  vsprintf(debug_bfr, fmt, args);
  va_end(args);

  UART_sendString(DEBUG, debug_bfr);
  /* HAL_Delay(2); */
}

