//***************************************************************************
// Copyright (C) 2012 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: Ricardo Martins                                                  *
//***************************************************************************
// $Id:: wdt.h 5237 2012-12-03 22:17:12Z rasm                             $:*
//***************************************************************************

#ifndef UCTK_XMEGA_WDT_H_INCLUDED_
#define UCTK_XMEGA_WDT_H_INCLUDED_

// AVR libc headers.
#include <avr/io.h>

// UCTK headers.
#include "ccp.h"

static inline void
wdt_enable(WDT_PER_t period)
{
  uctk_ccp_write(&WDT.CTRL, period | WDT_CEN_bm | WDT_ENABLE_bm);
}

static inline void
wdt_disable(void)
{
  uint8_t tmp = (WDT.CTRL & ~WDT_ENABLE_bm) | WDT_CEN_bm;
  uctk_ccp_write(&WDT.CTRL, tmp);
}

static inline void
wdt_reset(void)
{
  __asm__ __volatile__("wdr");
}

#endif
