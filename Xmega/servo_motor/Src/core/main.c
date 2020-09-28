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
extern servo_motor servo_motor_disc;

int main(void)
{
  initUsart();

  cli();
  board_init();
  sei();

  spew("\n\nStart\n\n");

  //SERVO_CFG_ALARM_OUT(motor_disc, MOTOR_RSTALARM, true);
  while (1)
  {

    //UART_sendString(DEBUG, "hELLO\n"); //motor_disc.start_stop->pin);
    SERVO_START();
    SERVO_RUN();
    SERVO_SET_ALARM_RESET();
    _delay_ms(2000);
    //gpio_clr_np(motor_disc.start_stop->port, 3);
    SERVO_STOP();
    SERVO_BRAKE();
    SERVO_CLR_ALARM_RESET();
    _delay_ms(2000);
    spew("START_STOP:  %d, %d\n", servo_motor_disc.start_stop.porta, servo_motor_disc.start_stop.pino);
    spew("RUN_BRAKE:  %d, %d\n", servo_motor_disc.run_brake.porta, servo_motor_disc.run_brake.pino);
    spew("ALARM_IN:  %d, %d\n", servo_motor_disc.alarm.porta, servo_motor_disc.alarm.pino);
    spew("ALARM_OUT:  %d, %d\n", servo_motor_disc.reset_alarm.porta, servo_motor_disc.reset_alarm.pino);
    spew("SPEED_IN:  %d, %d\n\n", servo_motor_disc.speed_feedback.porta, servo_motor_disc.speed_feedback.pino);
  }
}
