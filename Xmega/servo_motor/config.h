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

//! UART peripheral.                    //57600
#define UART0                           (USARTD0)
//! UART receive port.
#define UART0_RX_PORT                   (PORTD)
//! UART receive pin.
#define UART0_RX_PIN                    (2)
//! UART transmit port.
#define UART0_TX_PORT                   (PORTD)
//! UART transmit pin.
#define UART0_TX_PIN                    (3)
//! Medium interrupt priority.
#define UART0_CTRLA                     (USART_RXCINTLVL_HI_gc)
#define UART0_CTRLB                     (USART_TXEN_bm | USART_RXEN_bm)
#define UART0_CTRLC                     (USART_CHSIZE_8BIT_gc)
#define UART0_BAUDCTRLA                 (0x22)
#define UART0_BAUDCTRLB                 (0)
//! UART receive interrupt vector.
#define DEBUG_RX_IVEC                   (USARTD0_RXC_vect)

#endif /* CONFIG_H_INCLUDED_ */