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

  _delay_ms(500);
  while (1)
  {
    
    gpio_set_np(motor_disc.start_stop->port, 3);
    //SERVO_START(motor_disc);
    //SERVO_RUN(motor_disc);
    //SERVO_SET_ALARM_RESET(motor_disc);
    _delay_ms(500);
    gpio_clr_np(motor_disc.start_stop->port, 3);
    //SERVO_STOP(motor_disc);
    //SERVO_BRAKE(motor_disc);
    //SERVO_CLR_ALARM_RESET(motor_disc);
    _delay_ms(500);
  }
}
