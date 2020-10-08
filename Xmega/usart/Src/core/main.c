//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: João Costa                                                       *
//***************************************************************************

#include "../../Inc/core/main.h"

int main(void)
{

  cli();
  board_init();
  initUsart();
  sei();

  spew("START\n");
  while (1)
  {
    if (is_new_command_available())
    {
      parse_cpu_data_rx(get_cpu_buffer());
      new_command_read_done();
    }

    //GPIO_TGL(LED);
  }
}