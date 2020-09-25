//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: João Costa                                                       *
//***************************************************************************

#include "../../Inc/core/main.h"

uint16_t T0_millis = 0;

int main(void)
{
  cli();
  board_init();
  sei();

  while (1)
  {
    if (T0_millis >= 1000)
    {
      GPIO_TGL(LED);
      T0_millis = 0;
    }
    for (int i = 0; i < 50; i++){}
  }
  return 0;
}

ISR(TCE0_OVF_vect)
{
  T0_millis++;
  //GPIO_TGL(LED);
}
