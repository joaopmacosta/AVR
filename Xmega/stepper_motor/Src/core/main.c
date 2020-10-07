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
int state = 1;
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
  spew("DIST MM: %d | STEPS: %d | SPEED MM: %d | SPEED STEP: %d | STEP TIME: %d\n", STEP_DISTANCE_MM, STEP_NUMBER, STEP_SPEED_MM_SEC, STEP_SPEED_STEPS_SEC, STEP_SPEED);
  while (1)
  {
    if (state == 1)
    {
      var = move_forward();
      if (var != 0){
        state = 0;
        break;}
    }
  }

  spew("Move done!\n");
}