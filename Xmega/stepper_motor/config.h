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

//! Stepper 1 select port/pin.
#define STEPPER1_A_PORT                 (PORTD)
#define STEPPER1_A_PIN                  (0)
#define STEPPER1_a_PORT                 (PORTD)
#define STEPPER1_a_PIN                  (1)
#define STEPPER1_B_PORT                 (PORTD)
#define STEPPER1_B_PIN                  (4)
#define STEPPER1_b_PORT                 (PORTD)
#define STEPPER1_b_PIN                  (5)

#define MICROSTTEPING_ENABLED           (false)

#define STEP_DISTANCE_MM                (30)  //linear mm
#define STEP_MM_PER_DEG                 (2)   //distance per degree a.k.a wheel radius
#define STEP_MIN_DEG                    (1)   //degrees per phase

#define STEP_SPEED_MM_SEC               (60)  //


//! UART peripheral.                    //57600
#define UART0                           (USARTC0)
//! UART receive port.
#define UART0_RX_PORT                   (PORTC)
//! UART receive pin.
#define UART0_RX_PIN                    (2)
//! UART transmit port.
#define UART0_TX_PORT                   (PORTC)
//! UART transmit pin.
#define UART0_TX_PIN                    (3)
//! Medium interrupt priority.
#define UART0_CTRLA                     (USART_RXCINTLVL_HI_gc)
#define UART0_CTRLB                     (USART_TXEN_bm | USART_RXEN_bm)
#define UART0_CTRLC                     (USART_CHSIZE_8BIT_gc)
#define UART0_BAUDCTRLA                 (0x22)
#define UART0_BAUDCTRLB                 (0)
//! UART receive interrupt vector.
#define DEBUG_RX_IVEC                   (USARTC0_RXC_vect)


#endif /* CONFIG_H_INCLUDED_ */