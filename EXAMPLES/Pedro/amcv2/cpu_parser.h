//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: Pedro Gonçalves                                                  *
//***************************************************************************

#ifndef CPU_PARSER_H_INCLUDED_
#define CPU_PARSER_H_INCLUDED_

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
  STATE        = 0,
  ALL          = 1
} parser_rx_data_cpu;

struct cpuData
{
    int id_motor;
    int set_rpm;
};

struct motorSpeedValues
{
    int speed_target;
    int actual_speed;
};

struct cpuData _cpuData;

struct motorSpeedValues _motorSpeedValues[NUMBER_OF_MOTORS];

void
init_cpu_parser(void);

void
set_led_motor(int id, bool turnOn);

void
cpu_praser(uint8_t data);

void
parse_cpu_data_rx(char * data_rx);

void
set_speed_taget(int id, int value);

void
set_rpm(int id);

int
pid_of_speed(int actual, int target);

#endif /* CPU_PARSER_H_ */