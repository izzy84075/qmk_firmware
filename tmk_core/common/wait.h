#ifndef WAIT_H
#define WAIT_H

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__AVR__)
#   include <util/delay.h>
#   define wait_ms(ms)  _delay_ms(ms)
#   define wait_us(us)  _delay_us(us)
#elif defined(PROTOCOL_CHIBIOS)
#   include "ch.h"
#   define wait_ms(ms) chThdSleep(MS2ST(ms))
#   define wait_us(us) chThdSleep(US2ST(us))
#elif defined(__arm__)
#   include "wait_api.h"
#else  // Unit tests
void wait_ms(uint32_t ms);
#define wait_us(us) wait_ms(us / 1000)
#endif

#ifdef __cplusplus
}
#endif

#endif
