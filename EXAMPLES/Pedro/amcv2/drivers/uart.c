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
#include "uart.h"
#include "io.h"
#include "../config.h"

#include "../motor_parser.h"
#include "../cpu_parser.h"

int cnt_reset_stop_emerg = 0;
char *text_emerg = "$S,0*";

void
initUsart(void)
{
  //DEBUG
  USARTE0_BAUDCTRLB = UART0_BAUDCTRLB;
  USARTE0_BAUDCTRLA = UART0_BAUDCTRLA;
  USARTE0_CTRLA = UART0_CTRLA;
  USARTE0_CTRLB = UART0_CTRLB;
  USARTE0_CTRLC = UART0_CTRLC;

  //MOTOR 0
  USARTC0_BAUDCTRLB = UART4_BAUDCTRLB;
  USARTC0_BAUDCTRLA = UART4_BAUDCTRLA;
  USARTC0_CTRLA = UART4_CTRLA;
  USARTC0_CTRLB = UART4_CTRLB;
  USARTC0_CTRLC = UART4_CTRLC;

  //MOTOR 1
  USARTC1_BAUDCTRLB = UART3_BAUDCTRLB;
  USARTC1_BAUDCTRLA = UART3_BAUDCTRLA;
  USARTC1_CTRLA = UART3_CTRLA;
  USARTC1_CTRLB = UART3_CTRLB;
  USARTC1_CTRLC = UART3_CTRLC;

  //MOTOR 2
  USARTD0_BAUDCTRLB = UART2_BAUDCTRLB;
  USARTD0_BAUDCTRLA = UART2_BAUDCTRLA;
  USARTD0_CTRLA = UART2_CTRLA;
  USARTD0_CTRLB = UART2_CTRLB;
  USARTD0_CTRLC = UART2_CTRLC;

  //MOTOR 3
  USARTD1_BAUDCTRLB = UART1_BAUDCTRLB;
  USARTD1_BAUDCTRLA = UART1_BAUDCTRLA;
  USARTD1_CTRLA = UART1_CTRLA;
  USARTD1_CTRLB = UART1_CTRLB;
  USARTD1_CTRLC = UART1_CTRLC;
}

void
UART_sendChar(uint8_t usart, uint8_t data)
{
  switch (usart)
  {
  case DEBUG:
    while (!(USARTE0_STATUS & USART_DREIF_bm));
    USARTE0_DATA = data;
    break;

  case MOTOR0:
    while (!(USARTC0_STATUS & USART_DREIF_bm));
    USARTC0_DATA = data;
    break;

  case MOTOR1:
    while (!(USARTC1_STATUS & USART_DREIF_bm));
    USARTC1_DATA = data;
    break;

  case MOTOR2:
    while (!(USARTD0_STATUS & USART_DREIF_bm));
    USARTD0_DATA = data;
    break;

  case MOTOR3:
    while (!(USARTD1_STATUS & USART_DREIF_bm));
    USARTD1_DATA = data;
    break;

  default:
    break;
  }
}

void
UART_sendString(uint8_t usart, char *str)
{
  register char c;
  while ((c = *str++))
    UART_sendChar(usart, c);
}

void
UART_sendInt(uint8_t usart, int value)
{
  char string[17];
  UART_sendString(usart, itoa(value, string, 10)); // base 10
}

void
UART_sendLint(uint8_t usart, long int data)
{
  char buf[33];
  UART_sendString(usart, ltoa(data, buf, 10));
}

//DEBUG
ISR(DEBUG_RX_IVEC)
{
  cpu_praser(USARTE0_DATA);
  cnt_reset_stop_emerg = 0;
}

//MOTOR 0
ISR(MOTOR_0_RX_IVEC)
{
  parse_motor0(USARTC0_DATA);
}

//MOTOR 1
ISR(MOTOR_1_RX_IVEC)
{
  parse_motor1(USARTC1_DATA);
}

//MOTOR 2
ISR(MOTOR_2_RX_IVEC)
{
  parse_motor2(USARTD0_DATA);
}

//MOTOR 3
ISR(MOTOR_3_RX_IVEC)
{
  parse_motor3(USARTD1_DATA);
}