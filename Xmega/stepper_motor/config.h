//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: Pedro Gonçalves                                                  *
//***************************************************************************

#ifndef CONFIG_H_INCLUDED_
#define CONFIG_H_INCLUDED_


//***************************************************************************
// GPIO.                                                                    *
//***************************************************************************

//! Valve 1 select port/pin.
#define LED_PORT                        (PORTC)
#define LED_PIN                         (0)

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

//! Stepper 1 select port/pin.
#define STEPPER1_A_PORT                  (PORTD)
#define STEPPER1_A_PIN                   (0)
#define STEPPER1_a_PORT                  (PORTD)
#define STEPPER1_a_PIN                   (1)
#define STEPPER1_B_PORT                  (PORTD)
#define STEPPER1_B_PIN                   (4)
#define STEPPER1_b_PORT                  (PORTD)
#define STEPPER1_b_PIN                   (5)

#define MICROSTTEPING_ENABLED            (false)

#endif /* CONFIG_H_INCLUDED_ */