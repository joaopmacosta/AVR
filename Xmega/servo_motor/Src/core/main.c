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

  initUsart();
  spew("\n\nStart\n\n");

  SERVO_CFG_START(motor_disc, MOTOR_STARTSTOP, true);
  SERVO_CFG_BRAKE(motor_disc, MOTOR_RUNBRAKE, true);
  //SERVO_CFG_ALARM_OUT(motor_disc, MOTOR_RSTALARM, true);
  int a = 10;
  while (1)
  {

    //UART_sendString(DEBUG, "hELLO\n"); //motor_disc.start_stop->pin);
    //SERVO_START(motor_disc);
    //SERVO_RUN(motor_disc);
    //SERVO_SET_ALARM_RESET(motor_disc);
    _delay_ms(500);
    //gpio_clr_np(motor_disc.start_stop->port, 3);
    //SERVO_STOP(motor_disc);
    //SERVO_BRAKE(motor_disc);
    //SERVO_CLR_ALARM_RESET(motor_disc);
    spew("start-stop: %d / %d\n", motor_disc.start_stop.pino, motor_disc.run_brake.pino);
  }
}
