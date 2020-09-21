//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: Pedro Gonçalves                                                  *
//***************************************************************************
// Based on UCTK Lib                                                        *
//***************************************************************************

#ifndef IO_H_
#define IO_H_

// ISO C 99 headers.
#include <stdbool.h>

// AVR headers.
#include <avr/io.h>

//adapted from uctk lib

#define GPIO(name)                          \
  {                                         \
    .port = &name##_PORT, .pin = name##_PIN \
  }
#define GPIO_CFG_OUT(name, val) gpio_cfg_out_np(&name##_PORT, name##_PIN, val)
#define GPIO_CFG_IN(name) gpio_cfg_in_np(&name##_PORT, name##_PIN)
#define GPIO_CFG_OPC(name, opc) gpio_cfg_opc_np(&name##_PORT, name##_PIN, opc)
#define GPIO_CFG_ISC(name, isc) gpio_cfg_isc_np(&name##_PORT, name##_PIN, isc)
#define GPIO_CFG_INV(name) gpio_cfg_inv_np(&name##_PORT, name##_PIN)
#define GPIO_TGL(name) gpio_tgl_np(&name##_PORT, name##_PIN)
#define GPIO_SET(name) gpio_set_np(&name##_PORT, name##_PIN)
#define GPIO_CLR(name) gpio_clr_np(&name##_PORT, name##_PIN)
#define GPIO_IS_SET(name) gpio_is_set_np(&name##_PORT, name##_PIN)

typedef enum
{
  GPIO_OPC_TOTEM = PORT_OPC_TOTEM_gc,
  GPIO_OPC_BUSKEEPER = PORT_OPC_BUSKEEPER_gc,
  GPIO_OPC_PULLDOWN = PORT_OPC_PULLDOWN_gc,
  GPIO_OPC_PULLUP = PORT_OPC_PULLUP_gc,
  GPIO_OPC_WIREDOR = PORT_OPC_WIREDOR_gc,
  GPIO_OPC_WIREDAND = PORT_OPC_WIREDAND_gc,
  GPIO_OPC_WIREDORPULL = PORT_OPC_WIREDORPULL_gc,
  GPIO_OPC_WIREDANDPULL = PORT_OPC_WIREDANDPULL_gc
} gpio_opc_t;

typedef enum
{
  GPIO_ISC_BOTHEDGES = PORT_ISC_BOTHEDGES_gc,
  GPIO_ISC_RISING = PORT_ISC_RISING_gc,
  GPIO_ISC_FALLING = PORT_ISC_FALLING_gc,
  GPIO_ISC_LEVEL = PORT_ISC_LEVEL_gc,
  GPIO_ISC_DISABLE = PORT_ISC_INPUT_DISABLE_gc
} gpio_isc_t;

struct gpio
{
  PORT_t *port;
  uint8_t pin;
};

typedef struct gpio *gpio_t;

void gpio_cfg_out_np(PORT_t *port, uint8_t pin, bool value);

void gpio_cfg_in_np(PORT_t *port, uint8_t pin);

void gpio_cfg_opc_np(PORT_t *port, uint8_t pin, gpio_opc_t opc);

void gpio_cfg_isc_np(PORT_t *port, uint8_t pin, gpio_isc_t isc);

void gpio_cfg_inv_np(PORT_t *port, uint8_t pin);

void gpio_set_np(PORT_t *port, uint8_t pin);

void gpio_clr_np(PORT_t *port, uint8_t pin);

void gpio_tgl_np(PORT_t *port, uint8_t pin);

bool gpio_is_set_np(PORT_t *port, uint8_t pin);

void gpio_cfg_out(gpio_t gpio, uint8_t value);

void gpio_cfg_in(gpio_t gpio);

void gpio_cfg_opc(gpio_t gpio, gpio_opc_t opc);

void gpio_set(gpio_t gpio);

void gpio_clr(gpio_t gpio);

void gpio_tgl(gpio_t gpio);

bool gpio_is_set(gpio_t gpio);

#endif /* IO_H_ */