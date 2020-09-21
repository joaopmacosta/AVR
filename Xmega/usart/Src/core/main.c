//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: João Costa                                                       *
//***************************************************************************

#include "../../Inc/core/main.h"

/*! Define that selects the Usart used in example. */
#define USART USARTC0

/*! Success variable, used to test driver. */
bool success;

int main(void)
{
  cli();
  board_init();
  sei();

}
