//***************************************************************************
// Copyright (C) 2012 Laboratório de Sistemas e Tecnologia Subaquática      *
// Departamento de Engenharia Electrotécnica e de Computadores              *
// Rua Dr. Roberto Frias, 4200-465 Porto, Portugal                          *
//***************************************************************************
// Author: Ricardo Martins                                                  *
//***************************************************************************
// $Id::                                                                  $:*
//***************************************************************************

#ifndef UCTK_XMEGA_CCP_H_INCLUDED_
#define UCTK_XMEGA_CCP_H_INCLUDED_

// AVR libc headers.
#include <avr/io.h>
#include <util/atomic.h>

static inline void
uctk_ccp_write(volatile uint8_t* address, uint8_t value)
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    volatile uint8_t* tmp = address;

#ifdef RAMPZ
    RAMPZ = 0;
#endif

    __asm__ __volatile__
    (
     "movw r30,  %0" "\n\t"
     "ldi  r16,  %2" "\n\t"
     "out   %3, r16" "\n\t"
     "st     Z,  %1" "\n\t"
     :
     : "r" (tmp), "r" (value), "M" (CCP_IOREG_gc), "i" (&CCP)
     : "r16", "r30", "r31"
    );
  }
}

#endif
