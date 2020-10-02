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

#define FLOW_SENSOR_PORT                (PORTD)
#define FLOW_SENSOR_PIN                 (0)

#define CALIBRATION_FACTOR              (4.5 * (4250/500)) //4.5;
#define FLOW_REFRESH_TIME               (1000) //ms

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