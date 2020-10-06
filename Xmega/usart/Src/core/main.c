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
    _delay_ms(1000);

    if (check_new_command())
    {
      parse_cpu_data_rx(get_cpu_cmd());
      spew("cmd: %d, %d, %d\n", _cpuData.arg1, _cpuData.arg2, _cpuData.arg3);
      new_command_read();
    }

    //GPIO_TGL(LED);
  }
}