//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: João Costa                                                       *
//***************************************************************************

#include "../../Inc/core/main.h"

uint32_t time = 0;
int var = 0;
int main(void)
{
  cli();
  board_init();
  clock_init();
  initUsart();
  sei();

  spew("START\n");
  //time = get_timer_value();
  set_step_timer();
  reset_step_count();

  do
  {
    _delay_ms(100);
    var = move_forward();
  } while (var != 1);


spew("Move done!\n");
}