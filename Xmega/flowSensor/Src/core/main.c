//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: João Costa                                                       *
//***************************************************************************

#include "../../Inc/core/main.h"

/*! Success variable, used to test driver. */
extern int end_stop1;

int main(void)
{
  cli();
  board_init();
  clock_init();
  initUsart();
  sei();

  spew("START\n");

  while (1)
  {
    /* NO INTERRUPTS MODE*/
    /*read_end_stops();*/
    for (int i; i < 50; i++){}
  }
}