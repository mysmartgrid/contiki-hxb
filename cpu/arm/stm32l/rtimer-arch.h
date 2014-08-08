#ifndef RTIMER_ARCH_H_664A91919334BB76
#define RTIMER_ARCH_H_664A91919334BB76

#include "sys/rtimer.h"

#define RTIMER_ARCH_SECOND (MCK/1024)

rtimer_clock_t rtimer_arch_now(void);

#endif
