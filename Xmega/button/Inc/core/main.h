#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

// ISO C99 headers.
#include <stdbool.h>

// AVR headers.
#include <util/atomic.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Local headers.

#include "../../Inc/core/board_init.h"
#include "../../Inc/driver/io.h"
#include "../../Inc/core/inputs.h"
#include "../../TC_driver/avr_compiler.h"

/*! Number of bytes to send in test example. */
#define NUM_BYTES 3

#endif