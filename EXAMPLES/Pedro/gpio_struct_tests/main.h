#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct
{
  char *porta;
  uint8_t pino;
  bool state;
} Motor;

Motor motor_struct;

typedef struct
{
  Motor motor_struct1;
  Motor motor_struct2;
  Motor motor_struct3;
  Motor motor_struct4;
} TodosMotores;

TodosMotores allMotor;

void setMotors(void);
void clearMotors(void);
void readValues(void);
void gpio_set_np(char *porta, uint8_t pino, uint8_t id);
void gpio_clr_np(char *porta, uint8_t pino, uint8_t id);
void spew(const char *fmt, ...);

#define GPIO_SET(name) gpio_set_np(name##_PORT, name##_PIN, name##_ID)
#define GPIO_CLR(name) gpio_clr_np(name##_PORT, name##_PIN, name##_ID)

//MOTOR 0
#define LED_MOTOR_0_PORT "PORTA"
#define LED_MOTOR_0_PIN (1)
#define LED_MOTOR_0_ID (1)
//MOTOR 1
#define LED_MOTOR_1_PORT "PORTB"
#define LED_MOTOR_1_PIN (2)
#define LED_MOTOR_1_ID (2)
//MOTOR 2
#define LED_MOTOR_2_PORT "PORTC"
#define LED_MOTOR_2_PIN (3)
#define LED_MOTOR_2_ID (3)
//MOTOR 3
#define LED_MOTOR_3_PORT "PORTD"
#define LED_MOTOR_3_PIN (4)
#define LED_MOTOR_3_ID (4)
