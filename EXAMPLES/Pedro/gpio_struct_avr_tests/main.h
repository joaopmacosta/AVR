#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct PORT_struct
{
  uint8_t DIR;      /* I/O Port Data Direction */
  uint8_t DIRSET;   /* I/O Port Data Direction Set */
  uint8_t DIRCLR;   /* I/O Port Data Direction Clear */
  uint8_t DIRTGL;   /* I/O Port Data Direction Toggle */
  uint8_t OUT;      /* I/O Port Output */
  uint8_t OUTSET;   /* I/O Port Output Set */
  uint8_t OUTCLR;   /* I/O Port Output Clear */
  uint8_t OUTTGL;   /* I/O Port Output Toggle */
  uint8_t IN;       /* I/O port Input */
  uint8_t INTCTRL;  /* Interrupt Control Register */
  uint8_t INT0MASK; /* Port Interrupt 0 Mask */
  uint8_t INT1MASK; /* Port Interrupt 1 Mask */
  uint8_t INTFLAGS; /* Interrupt Flag Register */
  uint8_t reserved_0x0D;
  uint8_t REMAP; /* I/O Port Pin Remap Register */
  uint8_t reserved_0x0F;
  uint8_t PIN0CTRL; /* Pin 0 Control Register */
  uint8_t PIN1CTRL; /* Pin 1 Control Register */
  uint8_t PIN2CTRL; /* Pin 2 Control Register */
  uint8_t PIN3CTRL; /* Pin 3 Control Register */
  uint8_t PIN4CTRL; /* Pin 4 Control Register */
  uint8_t PIN5CTRL; /* Pin 5 Control Register */
  uint8_t PIN6CTRL; /* Pin 6 Control Register */
  uint8_t PIN7CTRL; /* Pin 7 Control Register */
} PORT_t;

typedef struct
{
  PORT_t *porta;
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
void gpio_set_np(PORT_t *porta, uint8_t pino, uint8_t id);
void gpio_clr_np(PORT_t *porta, uint8_t pino, uint8_t id);
void spew(const char *fmt, ...);

#define GPIO_SET(name)                   gpio_set_np(&name ## _PORT, name ## _PIN, name ## _ID)
#define GPIO_CLR(name)                   gpio_clr_np(&name ## _PORT, name ## _PIN, name ## _ID)

#define PORTA                            (*(PORT_t *) 0x0600)  /* I/O Ports */
#define PORTB                            (*(PORT_t *) 0x0620)  /* I/O Ports */
#define PORTC                            (*(PORT_t *) 0x0640)  /* I/O Ports */
#define PORTD                            (*(PORT_t *) 0x0660)  /* I/O Ports */

//MOTOR 0
#define LED_MOTOR_0_PORT                 (PORTA)
#define LED_MOTOR_0_PIN                  (1)
#define LED_MOTOR_0_ID                   (1)
//MOTOR 1
#define LED_MOTOR_1_PORT                 (PORTB)
#define LED_MOTOR_1_PIN                  (2)
#define LED_MOTOR_1_ID                   (2)
//MOTOR 2
#define LED_MOTOR_2_PORT                 (PORTC)
#define LED_MOTOR_2_PIN                  (3)
#define LED_MOTOR_2_ID                   (3)
//MOTOR 3
#define LED_MOTOR_3_PORT                 (PORTD)
#define LED_MOTOR_3_PIN                  (4)
#define LED_MOTOR_3_ID                   (4)
