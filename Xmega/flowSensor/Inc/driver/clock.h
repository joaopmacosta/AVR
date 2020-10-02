//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: João Costa                                                       *
//***************************************************************************

#ifndef CLOCK_H_INCLUDED_
#define CLOCK_H_INCLUDED_

/// ISO C 99 headers.
#include <stddef.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// AVR headers.
#include <avr/io.h>

void clock_init(void);

uint16_t get_timer_value(void);

#endif //CLOCK_H_INCLUDED_