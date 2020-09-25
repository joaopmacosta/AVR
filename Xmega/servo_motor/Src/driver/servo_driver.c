#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdbool.h>

#include "../../Inc/driver/io.h"
#include "../../Inc/driver/servo_driver.h"
#include "../../Inc/driver/uart.h"

void servo_cfg_start(servo_motor_t servo, PORT_t *port, uint8_t pin, bool value)
{
  spew("cfg: %d\n", pin);
  servo.start_stop.porta = port;
  servo.start_stop.pino = pin;
  gpio_cfg_out_np(port, pin, value);
}

void servo_cfg_brake(servo_motor_t servo, PORT_t *port, uint8_t pin, bool value)
{
  spew("cfg: start - %d | run - %d\n", servo.start_stop.pino, pin);
  servo.run_brake.porta = port;
  servo.run_brake.pino = pin;
  spew("cfg: start - %d | run - %d\n", servo.start_stop.pino, pin);
  gpio_cfg_out_np(port, pin, value);
}

void servo_cfg_alarm_in(servo_motor_t servo, PORT_t *port, uint8_t pin)
{
  servo.alarm.porta = port;
  servo.alarm.pino = pin;
  gpio_cfg_in_np(port, pin);
}

void servo_cfg_alarm_out(servo_motor_t servo, PORT_t *port, uint8_t pin, bool value)
{
  servo.reset_alarm.porta = port;
  servo.reset_alarm.pino = pin;
  gpio_cfg_out_np(port, pin, value);
}

void servo_cfg_speed_in(servo_motor_t servo, PORT_t *port, uint8_t pin)
{
  servo.speed_feedback.porta = port;
  servo.reset_alarm.pino = pin;
  gpio_cfg_in_np(port, pin);
}

void servo_cfg_speed_out(servo_motor_t servo, PORT_t *port, uint8_t pin, bool value)
{
  servo.speed_feedback.porta = port;
  servo.reset_alarm.pino = pin;
  gpio_cfg_out_np(port, pin, value);
}

void servo_start(servo_motor_t servo)
{
  gpio_clr_np(servo.start_stop.porta, servo.start_stop.pino);
}

void servo_stop(servo_motor_t servo)
{
  gpio_set_np(servo.start_stop.porta, servo.start_stop.pino);
}

void servo_brake(servo_motor_t servo)
{
  gpio_clr_np(servo.run_brake.porta, servo.run_brake.pino);
}

void servo_run(servo_motor_t servo)
{
  gpio_set_np(servo.run_brake.porta, servo.run_brake.pino);
}

void servo_set_alarm_reset(servo_motor_t servo)
{
  gpio_set_np(servo.reset_alarm.porta, servo.reset_alarm.pino);
}

void servo_clr_alarm_reset(servo_motor_t servo)
{
  gpio_clr_np(servo.reset_alarm.porta, servo.reset_alarm.pino);
}