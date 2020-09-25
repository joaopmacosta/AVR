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
    SERVO_START(motor_disc);
    SERVO_BRAKE(motor_disc);
    _delay_ms(1000);
    SERVO_STOP(motor_disc);
    SERVO_RUN(motor_disc);
    _delay_ms(1000);

    /*
    //! Motor Start/Stop select port/pin.
    #define MOTOR_STARTSTOP_PORT            (PORTC)
    #define MOTOR_STARTSTOP_PIN             (3)
    //! Motor Run/Brake select port/pin.
    #define MOTOR_RUNBRAKE_PORT             (PORTC)
    #define MOTOR_RUNBRAKE_PIN              (4)
    //! Motor Reset Alarm select port/pin.
    #define MOTOR_RSTALARM_PORT             (PORTC)
    #define MOTOR_RSTALARM_PIN              (5)
    //! Motor Alarm select port/pin.
    #define MOTOR_ALARM_PORT                (PORTC)
    #define MOTOR_ALARM_PIN                 (6)
    //! Motor Speed Feedback select port/pin.
    #define MOTOR_SPEEDOUT_PORT             (PORTC)
    #define MOTOR_SPEEDOUT_PIN              (7)
    */
  }
}
