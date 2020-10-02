#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdbool.h>

#include "../../Inc/driver/io.h"
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