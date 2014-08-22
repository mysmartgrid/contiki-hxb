#include <stm32l1xx.h>

#include <sys/clock.h>
#include <sys/cc.h>
#include <sys/etimer.h>

static volatile clock_time_t current_clock = 0;
static volatile unsigned long current_seconds = 0;
static unsigned int second_countdown = CLOCK_SECOND;

void SysTick_Handler(void) __attribute__ ((interrupt));

void SysTick_Handler(void)
{
	(void)SysTick->CTRL;
	SCB->ICSR = SCB_ICSR_PENDSTCLR;
	current_clock++;
	if (etimer_pending() && etimer_next_expiration_time() <= current_clock) {
		etimer_request_poll();
	}
	if (--second_countdown == 0) {
		current_seconds++;
		second_countdown = CLOCK_SECOND;
	}
}


void clock_init()
{
	SysTick_Config(MCK / CLOCK_SECOND);
}

clock_time_t clock_time(void)
{
	return current_clock;
}

unsigned long clock_seconds(void)
{
	return current_seconds;
}

void clock_wait(clock_time_t t)
{
	while (t--) {
		clock_time_t cur = clock_time();
		while (cur == clock_time());
	}
}

void clock_delay_usec(uint16_t dt)
{
	// loops = <us> * <cycles/us> * <cycles/loop>
	// <cycles/loop> = 1 (cbz) + 1 (subs) + 1 (b) + 2 (pipeline refill)
	uint32_t loops = dt * (MCK / 1000000) / 5;
	asm volatile (
		"1: cbz %0, 2f\n"
		"   subs %0, #1\n"
		"   b 1b\n"
		"2:"
		: "+r"(loops));
}
