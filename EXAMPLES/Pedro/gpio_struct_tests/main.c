#include "main.h"

char debug_bfr[512];

int main(void)
{
  spew("Set values\n");
  setMotors();
  readValues();
  spew("Clear values\n");
  clearMotors();
  readValues();
  return 0;
}

void setMotors(void)
{
  GPIO_SET(LED_MOTOR_0);
  GPIO_SET(LED_MOTOR_1);
  GPIO_SET(LED_MOTOR_2);
  GPIO_SET(LED_MOTOR_3);
}

void clearMotors(void)
{
  GPIO_CLR(LED_MOTOR_0);
  GPIO_CLR(LED_MOTOR_1);
  GPIO_CLR(LED_MOTOR_2);
  GPIO_CLR(LED_MOTOR_3);
}

void gpio_set_np(char *porta, uint8_t pino, uint8_t id)
{
  switch (id)
  {
  case 1:
    allMotor.motor_struct1.porta = porta;
    allMotor.motor_struct1.pino = pino;
    allMotor.motor_struct1.state = true;
    break;

  case 2:
    allMotor.motor_struct2.porta = porta;
    allMotor.motor_struct2.pino = pino;
    allMotor.motor_struct2.state = true;
    break;

  case 3:
    allMotor.motor_struct3.porta = porta;
    allMotor.motor_struct3.pino = pino;
    allMotor.motor_struct3.state = true;
    break;

  case 4:
    allMotor.motor_struct4.porta = porta;
    allMotor.motor_struct4.pino = pino;
    allMotor.motor_struct4.state = true;
    break;

  default:
    break;
  }
}

void gpio_clr_np(char *porta, uint8_t pino, uint8_t id)
{
  switch (id)
  {
  case 1:
    allMotor.motor_struct1.porta = porta;
    allMotor.motor_struct1.pino = pino;
    allMotor.motor_struct1.state = false;
    break;

  case 2:
    allMotor.motor_struct2.porta = porta;
    allMotor.motor_struct2.pino = pino;
    allMotor.motor_struct2.state = false;
    break;

  case 3:
    allMotor.motor_struct3.porta = porta;
    allMotor.motor_struct3.pino = pino;
    allMotor.motor_struct3.state = false;
    break;

  case 4:
    allMotor.motor_struct4.porta = porta;
    allMotor.motor_struct4.pino = pino;
    allMotor.motor_struct4.state = false;
    break;

  default:
    break;
  }
}

void readValues(void)
{
  spew("Motor 1 - PORT: %s | PIN: %d | Values: %d\n", allMotor.motor_struct1.porta, allMotor.motor_struct1.pino, allMotor.motor_struct1.state);
  spew("Motor 2 - PORT: %s | PIN: %d | Values: %d\n", allMotor.motor_struct2.porta, allMotor.motor_struct2.pino, allMotor.motor_struct2.state);
  spew("Motor 3 - PORT: %s | PIN: %d | Values: %d\n", allMotor.motor_struct3.porta, allMotor.motor_struct3.pino, allMotor.motor_struct3.state);
  spew("Motor 4 - PORT: %s | PIN: %d | Values: %d\n", allMotor.motor_struct4.porta, allMotor.motor_struct4.pino, allMotor.motor_struct4.state);
}

void spew(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vsprintf(debug_bfr, fmt, args);
  va_end(args);
  printf("%s",debug_bfr);
}