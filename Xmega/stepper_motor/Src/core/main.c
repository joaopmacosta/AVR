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
servo_motor_t motor_disc;

int main(void)
{
  cli();
  board_init();
  sei();

  while (1)
  {
  }
}
