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

  while (1)
  {
    _delay_ms(5000);
    UART_sendString(DEBUG, "Ping...\n");
    GPIO_TGL(LED);
  }
}