#ifndef SERVO_DRIVER_H_INCLUDED_
#define SERVO_DRIVER_H_INCLUDED_

// ISO C 99 headers.
#include <stdbool.h>

// AVR headers.
#include <avr/io.h>

#include "../../Inc/driver/io.h"

typedef struct
{
  PORT_t *porta;
  uint8_t pino;
} motor_pin;

motor_pin motor_pin_t;
// This structure contains all pins related to a servo motor
typedef struct 
{
  // Start/Stop
  motor_pin start_stop; 
  // Run/Brake
  motor_pin run_brake;
  // Alarms Input
  motor_pin alarm;
  // Reset Alarm
  motor_pin reset_alarm;
  // Speed Feedback
  motor_pin speed_feedback;
  // PWM Speed Command
  motor_pin speed_pwm;
} servo_motor;
 
servo_motor servo_motor_disc;

//#define SERVO_CFG_START(servo, name, val) servo_cfg_start(servo, &name##_PORT, name##_PIN, val)
#define SERVO_CFG_START(name, val) servo_cfg_start(&name##_PORT, name##_PIN, val)
//#define SERVO_CFG_BRAKE(servo, name, val) servo_cfg_brake(servo, &name##_PORT, name##_PIN, val)
#define SERVO_CFG_BRAKE(name, val) servo_cfg_brake(&name##_PORT, name##_PIN, val)
//#define SERVO_CFG_ALARM_IN(servo, name) servo_cfg_alarm_in(servo, &name##_PORT, name##_PIN)
#define SERVO_CFG_ALARM_IN(name) servo_cfg_alarm_in(&name##_PORT, name##_PIN)
//#define SERVO_CFG_ALARM_OUT(servo, name, val) servo_cfg_alarm_out(servo, &name##_PORT, name##_PIN, val)
#define SERVO_CFG_ALARM_OUT(name, val) servo_cfg_alarm_out(&name##_PORT, name##_PIN, val)
//#define SERVO_CFG_SPD_IN(servo, name) servo_cfg_speed_in(servo, &name##_PORT, name##_PIN)
#define SERVO_CFG_SPD_IN(name) servo_cfg_speed_in(&name##_PORT, name##_PIN)
//#define SERVO_CFG_SPD_OUT(servo, name, val) servo_cfg_speed_out(servo, &name##_PORT, name##_PIN, val)
#define SERVO_CFG_SPD_OUT(name, val) servo_cfg_speed_out(&name##_PORT, name##_PIN, val)
//#define SERVO_START(servo) servo_start(servo)
#define SERVO_START() servo_start()
//#define SERVO_STOP(servo) servo_stop(servo)
#define SERVO_STOP() servo_stop()
//#define SERVO_BRAKE(servo) servo_brake(servo)
#define SERVO_BRAKE() servo_brake()
//#define SERVO_RUN(servo) servo_run(servo)
#define SERVO_RUN() servo_run()
//#define SERVO_SET_ALARM_RESET(servo) servo_clr_alarm_reset(servo)
#define SERVO_SET_ALARM_RESET() servo_set_alarm_reset()
//#define SERVO_CLR_ALARM_RESET(servo) servo_clr_alarm_reset(servo)
#define SERVO_CLR_ALARM_RESET() servo_clr_alarm_reset()

void servo_cfg_start(/*servo_motor servo,*/ PORT_t *port, uint8_t pin, bool value);

void servo_cfg_brake(/*servo_motor servo,*/ PORT_t *port, uint8_t pin, bool value);

void servo_cfg_alarm_in(/*servo_motor servo*/ PORT_t *port, uint8_t pin);

void servo_cfg_alarm_out(/*servo_motor servo*/ PORT_t *port, uint8_t pin, bool value);

void servo_cfg_speed_in(/*servo_motor servo*/ PORT_t *port, uint8_t pin);

void servo_cfg_speed_out(/*servo_motor servo*/ PORT_t *port, uint8_t pin, bool value);

void servo_start(/*servo_motor servo*/ void);

void servo_stop(/*servo_motor servo*/ void);

void servo_brake(/*servo_motor servo*/ void);

void servo_run(/*servo_motor servo*/ void);

void servo_set_alarm_reset(/*servo_motor servo*/ void);

void servo_clr_alarm_reset(/*servo_motor servo*/ void);

#endif //SERVO_DRIVER_H_