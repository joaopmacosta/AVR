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
#define LED_PORT                (PORTC)
#define LED_PIN                 (0)

//! USARTD0 (WEATHER STATION) select port/pin
#define UART0_RX_PORT           (PORTC)
#define UART0_RX_PIN            (2)
#define UART0_TX_PORT           (PORTC)
#define UART0_TX_PIN            (3)

//! USARTD1 (DUNE) select port/pin
#define UART1_RX_PORT           (PORTD)
#define UART1_RX_PIN            (6)
#define UART1_TX_PORT           (PORTD)
#define UART1_TX_PIN            (7)

// Serial parameters
#define USART_RX_BUFFER_SIZE    (128)
#define USART_TX_BUFFER_SIZE    (128)

#define USART_CPU               (USARTC0)
#define USART0_DRE_INT_LVL      (USART_DREINTLVL_LO_gc)
#define USART0_RX_INT_LVL       (USART_RXCINTLVL_LO_gc)
#define USART0_DATA_BITS        (USART_CHSIZE_8BIT_gc)
#define USART0_PARITY_MODE      (USART_PMODE_DISABLED_gc)

#endif /* CONFIG_H_INCLUDED_ */