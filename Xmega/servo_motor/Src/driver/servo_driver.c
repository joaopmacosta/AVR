#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdbool.h>

#include "../../Inc/driver/io.h"
#include "../../Inc/driver/servo_driver.h"
#include "../../Inc/driver/uart.h"

void servo_cfg_start(/*servo_motor servo,*/ PORT_t *port, uint8_t pin, bool value)
{
  servo_motor_disc.start_stop.porta = port;
  servo_motor_disc.start_stop.pino = pin;
  //spew("arguments:  %d, %d\n", port, pin);
  //spew("start_stop:  %d, %d\n", servo_motor_disc.start_stop.porta, servo_motor_disc.start_stop.pino);
  gpio_cfg_out_np((PORT_t *)port, pin, value);
}

void servo_cfg_brake(/*servo_motor servo,*/ PORT_t *port, uint8_t pin, bool value)
{
  servo_motor_disc.run_brake.porta = port;
  servo_motor_disc.run_brake.pino = pin;
  //spew("arguments:  %d, %d\n", port, pin);
  //spew("run_brake:  %d, %d\n", servo_motor_disc.run_brake.porta, servo_motor_disc.run_brake.pino);
  gpio_cfg_out_np(port, pin, value);
}

void servo_cfg_alarm_in(/*servo_motor servo,*/ PORT_t *port, uint8_t pin)
{
  servo_motor_disc.alarm.porta = port;
  servo_motor_disc.alarm.pino = pin;
  //spew("arguments:  %d, %d\n", port, pin);
  //spew("alarm_in:  %d, %d\n", servo_motor_disc.alarm.porta, servo_motor_disc.alarm.pino);
  gpio_cfg_in_np(port, pin);
}

void servo_cfg_alarm_out(/*servo_motor servo,*/ PORT_t *port, uint8_t pin, bool value)
{
  servo_motor_disc.reset_alarm.porta = port;
  servo_motor_disc.reset_alarm.pino = pin;
  //spew("arguments:  %d, %d\n", port, pin);
  //spew("alarm_reset:  %d, %d\n", servo_motor_disc.reset_alarm.porta, servo_motor_disc.reset_alarm.pino);
  gpio_cfg_out_np(port, pin, value);
}

void servo_cfg_speed_in(/*servo_motor servo,*/ PORT_t *port, uint8_t pin)
{
  servo_motor_disc.speed_feedback.porta = port;
  servo_motor_disc.speed_feedback.pino = pin;
  //spew("arguments:  %d, %d\n", port, pin);
  //spew("speed_in:  %d, %d\n", servo_motor_disc.speed_feedback.porta, servo_motor_disc.speed_feedback.pino);
  gpio_cfg_in_np(port, pin);
}

void servo_cfg_speed_out(/*servo_motor servo,*/ PORT_t *port, uint8_t pin, bool value)
{
  servo_motor_disc.speed_pwm.porta = port;
  servo_motor_disc.speed_pwm.pino = pin;
  //spew("arguments:  %d, %d\n", port, pin);
  //spew("speed_out:  %d, %d\n", servo_motor_disc.start_stop.porta, servo_motor_disc.start_stop.pino);
  gpio_cfg_out_np(port, pin, value);
} 

void servo_start(/*servo_motor servo*/ void)
{
  gpio_clr_np(servo_motor_disc.start_stop.porta, servo_motor_disc.start_stop.pino);
}

void servo_stop(/*servo_motor servo*/ void)
{
  gpio_set_np(servo_motor_disc.start_stop.porta, servo_motor_disc.start_stop.pino);
}

void servo_brake(/*servo_motor servo*/ void)
{
  gpio_clr_np(servo_motor_disc.run_brake.porta, servo_motor_disc.run_brake.pino);
}

void servo_run(/*servo_motor servo*/ void)
{
  gpio_set_np(servo_motor_disc.run_brake.porta, servo_motor_disc.run_brake.pino);
}

void servo_set_alarm_reset(/*servo_motor servo*/ void)
{
  gpio_set_np(servo_motor_disc.reset_alarm.porta, servo_motor_disc.reset_alarm.pino);
}

void servo_clr_alarm_reset(/*servo_motor servo*/ void)
{
  gpio_clr_np(servo_motor_disc.reset_alarm.porta, servo_motor_disc.reset_alarm.pino);
}