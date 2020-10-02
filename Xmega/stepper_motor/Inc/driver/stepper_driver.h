#ifndef STEPPER_DRIVER_H_INCLUDED_
#define STEPPER_DRIVER_H_INCLUDED_

// ISO C 99 headers.
#include <stdbool.h>

// AVR headers.
#include <avr/io.h>

#include "../../Inc/driver/io.h"

// This structure contains stepper motor's pins
typedef struct
{
  // A
  gpio_t a;
  // A'
  gpio_t a_;
  // B
  gpio_t b;
  // B'
  gpio_t b_;
  // phase
  int phase[4];
} stepper_motor;

stepper_motor stepper_motor_t;

/*bool step_phase[8][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}};*/

#define STEPPER_CFG_PHASE(val) stepper_motor_t.phase = 0;
#define STEPPER_CFG_A(name, val) servo_cfg_A(&name##_PORT, name##_PIN, val)
#define STEPPER_CFG_A_(name, val) servo_cfg_A_(&name##_PORT, name##_PIN, val)
#define STEPPER_CFG_B(name, val) servo_cfg_B(&name##_PORT, name##_PIN, val)
#define STEPPER_CFG_B_(name, val) servo_cfg_B_(&name##_PORT, name##_PIN, val)

void servo_cfg_A(PORT_t *port, uint8_t pin, bool value);
void servo_cfg_A_(PORT_t *port, uint8_t pin, bool value);
void servo_cfg_B(PORT_t *port, uint8_t pin, bool value);
void servo_cfg_B_(PORT_t *port, uint8_t pin, bool value);

bool move_forward(uint8_t speed);

#endif //STEPPER_DRIVER_H_INCLUDED_