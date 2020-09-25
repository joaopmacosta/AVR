//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: Pedro Gonçalves                                                  *
//***************************************************************************

#ifndef UART_H_
#define UART_H_

/// ISO C 99 headers.
#include <stddef.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define UART_RX_BUF_SIZE 32 // rx buffer size

typedef enum
{
  DEBUG         = 4
} uart_channel;

void
initUsart(void);

void
UART_sendChar(uart_channel usart, uint8_t data);

void
UART_sendString(uart_channel usart, char *str);

void
UART_sendInt(uart_channel usart, int value);

void
UART_sendLint(uart_channel usart, long int data);

#endif /* UART_H_ */