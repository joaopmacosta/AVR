//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: João Costa                                                       *
//***************************************************************************

#include "../../Inc/core/main.h"

uint32_t time = 0;

int main(void)
{
  cli();
  board_init();
  clock_init();
  initUsart();
  sei();

  spew("START\n");
  time = get_timer_value();
  while (1)
  {
    get_flow1_value();

    if (get_timer_value() - time >= 1000)
    {
      GPIO_TGL(LED);
      time = get_timer_value();
    }
  }
}