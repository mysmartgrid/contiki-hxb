#include "dev/watchdog.h"

#include "stm32l1xx.h"

void watchdog_init(void)
{
	DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_IWDG_STOP;

	IWDG->KR = 0x5555;
	while (IWDG->SR & IWDG_SR_PVU);
	// max 1.7s timeout by default, min ~0.9s by hardware variations
	IWDG->PR = IWDG_PR_PR_1;
	IWDG->KR = 0xAAAA;
}

void watchdog_start(void)
{
	IWDG->KR = 0xCCCC;
}

void watchdog_periodic(void)
{
	IWDG->KR = 0xAAAA;
}

#if 0
#error watchdog_stop is not supported
void watchdog_stop(void)
{
}
#endif

void watchdog_reboot(void)
{
	NVIC_SystemReset();
}
