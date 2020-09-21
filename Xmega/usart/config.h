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
#define LED_PORT                     (PORTC)
#define LED_PIN                      (0)

//! USARTD0 (WEATHER STATION) select port/pin
#define UART0_RX_PORT                   (PORTD)
#define UART0_RX_PIN                    (2)
#define UART0_TX_PORT                   (PORTD)
#define UART0_TX_PIN                    (3)

//! USARTD1 (DUNE) select port/pin
#define UART1_RX_PORT                   (PORTD)
#define UART1_RX_PIN                    (6)
#define UART1_TX_PORT                   (PORTD)
#define UART1_TX_PIN                    (7)

// Serial parameters
#define CTL_RX_BUFFER_SIZE                (128)




#endif /* CONFIG_H_INCLUDED_ */