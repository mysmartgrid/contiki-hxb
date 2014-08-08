#include "stm32l1xx.h"

extern void _reset(void) __attribute__((interrupt));

void configure_system_clock(void) __attribute((weak));

static void unhandled_handler(void) __attribute__((interrupt));

#define UNHANDLED __attribute((weak, alias("unhandled_handler")))
void NMI_Handler(void) __attribute__((interrupt, weak, alias("default_NMI_Handler")));
void HardFault_Handler(void) __attribute__((interrupt, weak, alias("default_HardFault_Handler")));
void MemManage_Handler(void) __attribute__((interrupt, weak, alias("default_MemManage_Handler")));
void BusFault_Handler(void) __attribute__((interrupt, weak, alias("default_BusFault_Handler")));
void UsageFault_Handler(void) __attribute__((interrupt, weak, alias("default_UsageFault_Handler")));
void SVC_Handler(void) UNHANDLED;
void DebugMon_Handler(void) UNHANDLED;
void PendSV_Handler(void) UNHANDLED;
void SysTick_Handler(void) UNHANDLED;
void WWDG_IRQHandler(void) UNHANDLED;
void PVD_IRQHandler(void) UNHANDLED;
void TAMPER_STAMP_IRQHandler(void) UNHANDLED;
void RTC_WKUP_IRQHandler(void) UNHANDLED;
void FLASH_IRQHandler(void) UNHANDLED;
void RCC_IRQHandler(void) UNHANDLED;
void EXTI0_IRQHandler(void) UNHANDLED;
void EXTI1_IRQHandler(void) UNHANDLED;
void EXTI2_IRQHandler(void) UNHANDLED;
void EXTI3_IRQHandler(void) UNHANDLED;
void EXTI4_IRQHandler(void) UNHANDLED;
void DMA1_Channel1_IRQHandler(void) UNHANDLED;
void DMA1_Channel2_IRQHandler(void) UNHANDLED;
void DMA1_Channel3_IRQHandler(void) UNHANDLED;
void DMA1_Channel4_IRQHandler(void) UNHANDLED;
void DMA1_Channel5_IRQHandler(void) UNHANDLED;
void DMA1_Channel6_IRQHandler(void) UNHANDLED;
void DMA1_Channel7_IRQHandler(void) UNHANDLED;
void ADC1_IRQHandler(void) UNHANDLED;
void USB_HP_IRQHandler(void) UNHANDLED;
void USB_LP_IRQHandler(void) UNHANDLED;
void DAC_IRQHandler(void) UNHANDLED;
void COMP_IRQHandler(void) UNHANDLED;
void EXTI9_5_IRQHandler(void) UNHANDLED;
void LCD_IRQHandler(void) UNHANDLED;
void TIM9_IRQHandler(void) UNHANDLED;
void TIM10_IRQHandler(void) UNHANDLED;
void TIM11_IRQHandler(void) UNHANDLED;
void TIM2_IRQHandler(void) UNHANDLED;
void TIM3_IRQHandler(void) UNHANDLED;
void TIM4_IRQHandler(void) UNHANDLED;
void I2C1_EV_IRQHandler(void) UNHANDLED;
void I2C1_ER_IRQHandler(void) UNHANDLED;
void I2C2_EV_IRQHandler(void) UNHANDLED;
void I2C2_ER_IRQHandler(void) UNHANDLED;
void SPI1_IRQHandler(void) UNHANDLED;
void SPI2_IRQHandler(void) UNHANDLED;
void USART1_IRQHandler(void) UNHANDLED;
void USART2_IRQHandler(void) UNHANDLED;
void USART3_IRQHandler(void) UNHANDLED;
void EXTI15_10_IRQHandler(void) UNHANDLED;
void RTC_Alarm_IRQHandler(void) UNHANDLED;
void USB_FS_WKUP_IRQHandler(void) UNHANDLED;
void TIM6_IRQHandler(void) UNHANDLED;
void TIM7_IRQHandler(void) UNHANDLED;

void (*isr_vectors[])(void) __attribute__((section(".isr_vector"))) = {
	_reset,
	NMI_Handler,
	HardFault_Handler,
	MemManage_Handler,
	BusFault_Handler,
	UsageFault_Handler,
	0,
	0,
	0,
	0,
	SVC_Handler,
	DebugMon_Handler,
	0,
	PendSV_Handler,
	SysTick_Handler,
	WWDG_IRQHandler,
	PVD_IRQHandler,
	TAMPER_STAMP_IRQHandler,
	RTC_WKUP_IRQHandler,
	FLASH_IRQHandler,
	RCC_IRQHandler,
	EXTI0_IRQHandler,
	EXTI1_IRQHandler,
	EXTI2_IRQHandler,
	EXTI3_IRQHandler,
	EXTI4_IRQHandler,
	DMA1_Channel1_IRQHandler,
	DMA1_Channel2_IRQHandler,
	DMA1_Channel3_IRQHandler,
	DMA1_Channel4_IRQHandler,
	DMA1_Channel5_IRQHandler,
	DMA1_Channel6_IRQHandler,
	DMA1_Channel7_IRQHandler,
	ADC1_IRQHandler,
	USB_HP_IRQHandler,
	USB_LP_IRQHandler,
	DAC_IRQHandler,
	COMP_IRQHandler,
	EXTI9_5_IRQHandler,
	LCD_IRQHandler,
	TIM9_IRQHandler,
	TIM10_IRQHandler,
	TIM11_IRQHandler,
	TIM2_IRQHandler,
	TIM3_IRQHandler,
	TIM4_IRQHandler,
	I2C1_EV_IRQHandler,
	I2C1_ER_IRQHandler,
	I2C2_EV_IRQHandler,
	I2C2_ER_IRQHandler,
	SPI1_IRQHandler,
	SPI2_IRQHandler,
	USART1_IRQHandler,
	USART2_IRQHandler,
	USART3_IRQHandler,
	EXTI15_10_IRQHandler,
	RTC_Alarm_IRQHandler,
	USB_FS_WKUP_IRQHandler,
	TIM6_IRQHandler,
	TIM7_IRQHandler,
};

extern uint8_t _etext[];
extern uint8_t _data[];
extern uint8_t _edata[];

static void fill_data(void)
{
	uint8_t *src = _etext;
	uint8_t *dst = _data;

	while (dst != _edata)
		*dst++ = *src++;
}

extern uint8_t _bss[];
extern uint8_t _ebss[];

static void fill_bss(void)
{
	uint8_t *dst = _bss;

	while (dst != _ebss)
		*dst++ = 0;
}

void configure_system_clock(void)
{
}

void _pre_init(void)
{
	fill_data();
	fill_bss();

	SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA | SCB_SHCSR_BUSFAULTENA | SCB_SHCSR_USGFAULTENA;

	configure_system_clock();
}

void unhandled_handler(void)
{
	for(;;);
}

void default_NMI_Handler(void)
{
	for(;;);
}

void default_HardFault_Handler(void)
{
	for(;;);
}

void default_MemManage_Handler(void)
{
	for(;;);
}

void default_BusFault_Handler(void)
{
	for(;;);
}

void default_UsageFault_Handler(void)
{
	for(;;);
}
