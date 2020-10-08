//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: Pedro Gonçalves                                                  *
//***************************************************************************

#ifndef CPU_PARSER_H_INCLUDED_
#define CPU_PARSER_H_INCLUDED_

#include "../../config.h"

/// ISO C 99 headers.
#include <stddef.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum
{
  STATE = 0,
  ALL = 1
} parser_rx_data_cpu;

struct cpuData
{
  int cmd;
  int arg1;
  int arg2;
};

struct cpuData _cpuData;

typedef enum
{
  PARSER = 0,
  DATA = 1,
  CSUM = 2
} parser_state;

//void init_cpu_parser(void);

void cpu_parser(uint8_t data);

//bool read_new_command(void);

void parse_cpu_data_rx(char *data_rx);

char* get_cpu_buffer(void);

bool is_new_command_available(void);

void new_command_read_done(void);

#endif /* CPU_PARSER_H_ */