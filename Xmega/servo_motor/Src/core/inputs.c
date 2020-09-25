#include "../../Inc/core/inputs.h"
#include "../../Inc/driver/io.h"
#include "../../TC_driver/avr_compiler.h"
#include "../../config.h"

// VARS

//end stop1
int switch1 = 1;
int last_switch1;
int end_stop1 = 0;

void read_end_stops(void)
{
  /* NO INTERRUPTS MODE*/
  /*// End Stop 1
  last_switch1 = switch1;
  switch1 = GPIO_IS_SET(BUTTON);
  if (switch1 && !last_switch1)
  {
    end_stop1 = 1;
  }*/
}

ISR(PORTC_INT0_vect)
{
  GPIO_TGL(LED);
}