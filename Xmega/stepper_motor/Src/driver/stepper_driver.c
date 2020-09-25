#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdbool.h>

#include "../../Inc/driver/io.h"
#include "../../Inc/driver/servo_driver.h"

void servo_cfg_start(servo_motor_t servo, PORT_t *port, uint8_t pin, bool value)
{
  servo.start_stop->port = port;
  servo.start_stop->pin = pin;
  gpio_cfg_out_np(port, pin, value);
}

void servo_cfg_brake(servo_motor_t servo, PORT_t *port, uint8_t pin, bool value)
{
  servo.run_brake->port = port;
  servo.run_brake->pin = pin;
  gpio_cfg_out_np(port, pin, value);
}

void servo_cfg_alarm_in(servo_motor_t servo, PORT_t *port, uint8_t pin)
{
  servo.alarm->port = port;
  servo.alarm->pin = pin;
  gpio_cfg_in_np(port, pin);
}

void servo_cfg_alarm_out(servo_motor_t servo, PORT_t *port, uint8_t pin, bool value)
{
  servo.reset_alarm->port = port;
  servo.reset_alarm->pin = pin;
  gpio_cfg_out_np(port, pin, value);
}

void servo_cfg_speed_in(servo_motor_t servo, PORT_t *port, uint8_t pin)
{
  servo.speed_feedback->port = port;
  servo.reset_alarm->pin = pin;
  gpio_cfg_in_np(port, pin);
}

void servo_cfg_speed_out(servo_motor_t servo, PORT_t *port, uint8_t pin, bool value)
{
  servo.speed_feedback->port = port;
  servo.reset_alarm->pin = pin;
  gpio_cfg_out_np(port, pin, value);
}

void servo_start(servo_motor_t servo)
{
  gpio_clr(servo.start_stop);
}

void servo_stop(servo_motor_t servo)
{
  gpio_set(servo.start_stop);
}

void servo_brake(servo_motor_t servo)
{
  gpio_clr(servo.run_brake);
}

void servo_run(servo_motor_t servo)
{
  gpio_set(servo.run_brake);
}