//***************************************************************************
// Copyright (C) 2017 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: Pedro Gonçalves                                                  *
//***************************************************************************
// Based on UCTK Lib                                                        *
//***************************************************************************

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include "../../Inc/driver/io.h"

void
gpio_cfg_out_np(PORT_t* port, uint8_t pin, bool value)
{
  if (value)
    port->OUTSET = (1 << pin);
  else
    port->OUTCLR = (1 << pin);

  port->DIRSET = (1 << pin);
}

void
gpio_cfg_in_np(PORT_t* port, uint8_t pin)
{
  port->DIRCLR = (1 << pin);
  port->OUTCLR = (1 << pin);
}

void
gpio_cfg_opc_np(PORT_t* port, uint8_t pin, gpio_opc_t opc)
{
  *(&port->PIN0CTRL + pin) |= opc;
}

void
gpio_cfg_isc_np(PORT_t* port, uint8_t pin, gpio_isc_t isc)
{
  *(&port->PIN0CTRL + pin) |= isc;
}

void
gpio_cfg_inv_np(PORT_t* port, uint8_t pin)
{
  *(&port->PIN0CTRL + pin) |= PORT_INVEN_bm;
}

void
gpio_set_np(PORT_t* port, uint8_t pin)
{
  port->OUTSET = (1 << pin);
}

void
gpio_clr_np(PORT_t* port, uint8_t pin)
{
  port->OUTCLR = (1 << pin);
}

void
gpio_tgl_np(PORT_t* port, uint8_t pin)
{
  port->OUTTGL = (1 << pin);
}

bool
gpio_is_set_np(PORT_t* port, uint8_t pin)
{
  return port->IN & (1 << pin);
}

void
gpio_cfg_out(gpio_t gpio, uint8_t value)
{
  gpio_cfg_out_np(gpio->port, gpio->pin, value);
}

void
gpio_cfg_in(gpio_t gpio)
{
  gpio_cfg_in_np(gpio->port, gpio->pin);
}

void
gpio_cfg_opc(gpio_t gpio, gpio_opc_t opc)
{
  gpio_cfg_opc_np(gpio->port, gpio->pin, opc);
}

void
gpio_set(gpio_t gpio)
{
  gpio_set_np(gpio->port, gpio->pin);
}

void
gpio_clr(gpio_t gpio)
{
  gpio_clr_np(gpio->port, gpio->pin);
}

void
gpio_tgl(gpio_t gpio)
{
  gpio_tgl_np(gpio->port, gpio->pin);
}

bool
gpio_is_set(gpio_t gpio)
{
  return gpio_is_set_np(gpio->port, gpio->pin);
}