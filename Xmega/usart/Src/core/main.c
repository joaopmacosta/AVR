//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: João Costa                                                       *
//***************************************************************************

#include "../../Inc/core/main.h"

/*! Number of bytes to send in test example. */
#define NUM_BYTES 3
/*! USART data struct used in example. */
USART_data_t USART_cpu;

/*! Test data to send. */
uint8_t sendArray[NUM_BYTES] = {0x55, 0xaa, 0xf0};
/*! Array to put received data in. */
uint8_t receiveArray[NUM_BYTES];
/*! Success variable, used to test driver. */
bool success;

int main(void)
{
  cli();
  board_init();
  sei();

  /* counter variable. */
  uint8_t i;
  while (1)
  {
    // Send sendArray. //
    i = 0;
    while (i < NUM_BYTES)
    {
      bool byteToBuffer;
      byteToBuffer = USART_TXBuffer_PutByte(&USART_cpu, sendArray[i]);
      if (byteToBuffer)
      {
        i++;
      }
    }

    // Fetch received data as it is received.
    i = 0;
    while (i < NUM_BYTES)
    {
      if (USART_RXBufferData_Available(&USART_cpu))
      {
        GPIO_TGL(LED);
        receiveArray[i] = USART_RXBuffer_GetByte(&USART_cpu);
        i++;
      }
    }

    // Test to see if sent data equals received data.
    // Assume success first.
    /*success = true;
    for (i = 0; i < NUM_BYTES; i++)
    {
      // Check that each element is received correctly.
      if (receiveArray[i] != sendArray[i])
      {
        success = false;
      }
    }

    // If success the program ends up inside the if statement.
    if (success)
    {
      GPIO_SET(LED);
    }
    else
    {
      GPIO_CLR(LED);
    }

    _delay_ms(1000);*/
  }
}

// Receive complete interrupt service routine.
ISR(USARTC0_RXC_vect)
{
  USART_RXComplete(&USART_cpu);
}

// Data register empty  interrupt service routine.
ISR(USARTC0_DRE_vect)
{
  USART_DataRegEmpty(&USART_cpu);
}
