#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdbool.h>

//#include "../../Inc/driver/io.h"
#include "../../Inc/driver/stepper_driver.h"

bool microstep_phase[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}};

void servo_cfg_A(PORT_t *port, uint8_t pin, bool value)
{
  stepper_motor_t.a->port = port;
  stepper_motor_t.a->pin = pin;
  gpio_cfg_out_np(port, pin, value);
}
void servo_cfg_A_(PORT_t *port, uint8_t pin, bool value)
{
  stepper_motor_t.a_->port = port;
  stepper_motor_t.a_->pin = pin;
  gpio_cfg_out_np(port, pin, value);
}
void servo_cfg_B(PORT_t *port, uint8_t pin, bool value)
{
  stepper_motor_t.b->port = port;
  stepper_motor_t.b->pin = pin;
  gpio_cfg_out_np(port, pin, value);
}
void servo_cfg_B_(PORT_t *port, uint8_t pin, bool value)
{
  stepper_motor_t.b_->port = port;
  stepper_motor_t.b_->pin = pin;
  gpio_cfg_out_np(port, pin, value);
}

uint16_t step_count = 0;
uint16_t step_timer = 0;

int move_forward()
{
  if (get_timer_value() - step_timer >= STEP_SPEED)
  {
    spew("%d\n", step_count);
    GPIO_TGL(LED);
    if (step_count < STEP_NUMBER)
    {
      stepper_motor_t.phase++;
      step_count++;
      if (stepper_motor_t.phase > 7)
      {
        stepper_motor_t.phase = 0;
      }
      set_step_timer();
      return 0; //MOVE NOT DONE YET
    }
    else
    {
      step_count = 0;
      stepper_motor_t.phase = 0;
      set_step_timer();
      return 1; //MOVE DONE
    }
  }
  return 0;
}

void set_step_timer(void)
{
  step_timer = get_timer_value();
}

void clear_step_timer(void)
{
  step_timer = 0;
}

void reset_step_count(void)
{
  step_count = 0;
}