#ifndef SERVO_DRIVER_H_INCLUDED_
#define SERVO_DRIVER_H_INCLUDED_

// ISO C 99 headers.
#include <stdbool.h>

// AVR headers.
#include <avr/io.h>

#include "../../Inc/driver/io.h"

// This structure contains all pins related to a servo motor
typedef struct servo_motor
{
  // Start/Stop
  gpio_t start_stop;
  // Run/Brake
  gpio_t run_brake;
  // Alarms Input
  gpio_t alarm;
  // Reset Alarm
  gpio_t reset_alarm;
  // Speed Feedback
  gpio_t speed_feedback;
  // PWM Speed Command
  gpio_t speed_pwm;
} servo_motor_t;

#define GPIO(name)                          \
  {                                         \
    .port = &name##_PORT, .pin = name##_PIN \
  }
#define SERVO_CFG_START(servo, name, val) servo_cfg_start(&servo, &name##_PORT, name##_PIN, val)
#define SERVO_CFG_BRAKE(servo, name, val) servo_cfg_brake(&servo, &name##_PORT, name##_PIN, val)
#define SERVO_CFG_ALARM_IN(servo, name) servo_cfg_alarm_in(servo, &name##_PORT, name##_PIN,)
#define SERVO_CFG_ALARM_OUT(servo, name, val) servo_cfg_alarm_out(servo, &name##_PORT, name##_PIN, val)
#define SERVO_CFG_SPD_IN(servo, name) servo_cfg_speed_in(servo, &name##_PORT, name##_PIN,)
#define SERVO_CFG_SPD_OUT(servo, name, val) servo_cfg_speed_out(servo, &name##_PORT, name##_PIN, val)
#define SERVO_START(servo) servo_start(servo)
#define SERVO_STOP(servo) servo_stop(servo)
#define SERVO_BRAKE(servo) servo_brake(servo)
#define SERVO_RUN(servo) servo_run(servo)
#define SERVO_SET_ALARM_RESET(servo) servo_set_alarm_reset(servo)
#define SERVO_CLR_ALARM_RESET(servo) servo_clr_alarm_reset(servo)

void servo_cfg_start(servo_motor_t *servo, PORT_t *port, uint8_t pin, bool value);

void servo_cfg_brake(servo_motor_t *servo, PORT_t *port, uint8_t pin, bool value);

void servo_cfg_alarm_in(servo_motor_t servo, PORT_t *port, uint8_t pin);

void servo_cfg_alarm_out(servo_motor_t servo, PORT_t *port, uint8_t pin, bool value);

void servo_cfg_speed_in(servo_motor_t servo, PORT_t *port, uint8_t pin);

void servo_cfg_speed_out(servo_motor_t servo, PORT_t *port, uint8_t pin, bool value);

void servo_start(servo_motor_t servo);

void servo_stop(servo_motor_t servo);

void servo_brake(servo_motor_t servo);

void servo_run(servo_motor_t servo);

void servo_set_alarm_reset(servo_motor_t servo);

void servo_clr_alarm_reset(servo_motor_t servo);

#endif //SERVO_DRIVER_H_