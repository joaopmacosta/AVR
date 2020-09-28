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
// General configurations                                                   *
//***************************************************************************

//! Watchdog period (1 s).
#define WDT_PERIOD                      (WDT_PER_2KCLK_gc)

#define MAX_VALUE_SPEED                 (32000)
#define MIN_VALUE_SPEED                 (-32000)

#define LOOP_SPEED                      (6)

#define NUMBER_OF_MOTORS                (4)

#define JUMP_VALUE_SPEED_PID            (3000)

#define TIME_TO_REFRESH_IS_ALIVE         (4) //x * 0.5s
#define TIME_TO_EMERG_STOP               (2) //x * TIME_TO_REFRESH_IS_ALIVE

//***************************************************************************
// UART0. Used by controller device                   32000000UL 57600      *
//***************************************************************************

//! UART peripheral.
#define UART0                           (USARTE0)
//! UART receive port.
#define UART0_RX_PORT                   (PORTE)
//! UART receive pin.
#define UART0_RX_PIN                    (2)
//! UART transmit port.
#define UART0_TX_PORT                   (PORTE)
//! UART transmit pin.
#define UART0_TX_PIN                    (3)
//! Medium interrupt priority.
#define UART0_CTRLA                     (USART_RXCINTLVL_HI_gc)
#define UART0_CTRLB                     (USART_TXEN_bm | USART_RXEN_bm)
#define UART0_CTRLC                     (USART_CHSIZE_8BIT_gc)
#define UART0_BAUDCTRLA                 (0x22)
#define UART0_BAUDCTRLB                 (0)
//! UART receive interrupt vector.
#define DEBUG_RX_IVEC                   (USARTE0_RXC_vect)

//***************************************************************************
// UART1. Used by controller device     MOTOR3        32000000UL 57600      *
//***************************************************************************

//! UART peripheral.
#define UART1                           (USARTD1)
//! UART receive port.
#define UART1_RX_PORT                   (PORTD)
//! UART receive pin.
#define UART1_RX_PIN                    (6)
//! UART transmit port.
#define UART1_TX_PORT                   (PORTD)
//! UART transmit pin.
#define UART1_TX_PIN                    (7)
//! Medium interrupt priority.
#define UART1_CTRLA                     (USART_RXCINTLVL_HI_gc)
#define UART1_CTRLB                     (USART_TXEN_bm | USART_RXEN_bm)
#define UART1_CTRLC                     (USART_CHSIZE_8BIT_gc)
#define UART1_BAUDCTRLA                 (0x22)
#define UART1_BAUDCTRLB                 (0)
//! UART receive interrupt vector.
#define MOTOR_3_RX_IVEC                 (USARTD1_RXC_vect)

//***************************************************************************
// UART2. Used by controller device     MOTOR2        32000000UL 57600      *
//***************************************************************************

//! UART peripheral.
#define UART2                           (USARTD0)
//! UART receive port.
#define UART2_RX_PORT                   (PORTD)
//! UART receive pin.
#define UART2_RX_PIN                    (2)
//! UART transmit port.
#define UART2_TX_PORT                   (PORTD)
//! UART transmit pin.
#define UART2_TX_PIN                    (3)
//! Medium interrupt priority.
#define UART2_CTRLA                     (USART_RXCINTLVL_HI_gc)
#define UART2_CTRLB                     (USART_TXEN_bm | USART_RXEN_bm)
#define UART2_CTRLC                     (USART_CHSIZE_8BIT_gc)
#define UART2_BAUDCTRLA                 (0x22)
#define UART2_BAUDCTRLB                 (0)
//! UART receive interrupt vector.
#define MOTOR_2_RX_IVEC                 (USARTD0_RXC_vect)

//***************************************************************************
// UART3. Used by controller device     MOTOR1        32000000UL 57600      *
//***************************************************************************

//! UART peripheral.
#define UART3                           (USARTC1)
//! UART receive port.
#define UART3_RX_PORT                   (PORTC)
//! UART receive pin.
#define UART3_RX_PIN                    (6)
//! UART transmit port.
#define UART3_TX_PORT                   (PORTC)
//! UART transmit pin.
#define UART3_TX_PIN                    (7)
//! Medium interrupt priority.
#define UART3_CTRLA                     (USART_RXCINTLVL_HI_gc)
#define UART3_CTRLB                     (USART_TXEN_bm | USART_RXEN_bm)
#define UART3_CTRLC                     (USART_CHSIZE_8BIT_gc)
#define UART3_BAUDCTRLA                 (0x22)
#define UART3_BAUDCTRLB                 (0)
//! UART receive interrupt vector.
#define MOTOR_1_RX_IVEC                 (USARTC1_RXC_vect)

//***************************************************************************
// UART4. Used by controller device     MOTOR0        32000000UL 57600      *
//***************************************************************************

//! UART peripheral.
#define UART4                           (USARTC0)
//! UART receive port.
#define UART4_RX_PORT                   (PORTC)
//! UART receive pin.
#define UART4_RX_PIN                    (2)
//! UART transmit port.
#define UART4_TX_PORT                   (PORTC)
//! UART transmit pin.
#define UART4_TX_PIN                    (3)
//! Medium interrupt priority.
#define UART4_CTRLA                     (USART_RXCINTLVL_HI_gc)
#define UART4_CTRLB                     (USART_TXEN_bm | USART_RXEN_bm)
#define UART4_CTRLC                     (USART_CHSIZE_8BIT_gc)
#define UART4_BAUDCTRLA                 (0x22) //57600
#define UART4_BAUDCTRLB                 (0)
//! UART receive interrupt vector.
#define MOTOR_0_RX_IVEC                 (USARTC0_RXC_vect)

//***************************************************************************
// GPIO.                                                                    *
//***************************************************************************

//MOTOR 0
#define LED_MOTOR_0_PORT                 (PORTC)
#define LED_MOTOR_0_PIN                  (4)
//MOTOR 1
#define LED_MOTOR_1_PORT                 (PORTC)
#define LED_MOTOR_1_PIN                  (5)
//MOTOR 2
#define LED_MOTOR_2_PORT                 (PORTD)
#define LED_MOTOR_2_PIN                  (4)
//MOTOR 3
#define LED_MOTOR_3_PORT                 (PORTD)
#define LED_MOTOR_3_PIN                  (5)

//! Led select port.
#define LED_DEBUG_PORT                   (LED_MOTOR_3_PORT)
//! Led select pin.
#define LED_DEBUG_PIN                    (LED_MOTOR_3_PIN)

#endif