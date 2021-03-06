#ifndef STEPPER_DRIVER_H_INCLUDED_
#define STEPPER_DRIVER_H_INCLUDED_

// ISO C 99 headers.
#include <stdbool.h>

// AVR headers.
#include <avr/io.h>

#include "uart.h"
#include "../../config.h"
#include "io.h"
#include "clock.h"

#define MM_PER_STEP                     (STEP_MM_PER_DEG * STEP_MIN_DEG)
#define STEP_NUMBER                     (STEP_DISTANCE_MM/MM_PER_STEP)
#define STEP_SPEED_STEPS_SEC            (STEP_SPEED_MM_SEC/MM_PER_STEP)
#define STEP_SPEED                      (1000/STEP_SPEED_STEPS_SEC)

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
  int phase;
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

int move_forward(void);
void set_step_timer(void);
void clear_step_timer(void);
void reset_step_count(void);

#endif //STEPPER_DRIVER_H_INCLUDED_