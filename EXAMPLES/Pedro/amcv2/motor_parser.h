//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: Pedro Gonçalves                                                  *
//***************************************************************************

#ifndef MOTOR_PARSER_H_INCLUDED_
#define MOTOR_PARSER_H_INCLUDED_

#include "config.h"

/// ISO C 99 headers.
#include <stddef.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum
{
  PARSER        = 0,
  DATA          = 1,
  CSUM          = 2
} parser_state;

typedef enum
{
  RPM        = 0,
  VOLT       = 1,
  AMP        = 2,
  TEMP       = 3
} parser_rx_data;

void
init_motor_parser(void);

void
parse_data_rx(uint8_t id_motor, char *data_rx);

void
parse_motor0(uint8_t data);

void
parse_motor1(uint8_t data);

void
parse_motor2(uint8_t data);

void
parse_motor3(uint8_t data);

#endif /* MOTOR_PARSER_H_ */