.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.section .init.head, "ax", %progbits
.type _reset, %function
.global _reset
_reset:
	bl _pre_init

.section .init.tail, "ax", %progbits
.type _init_tail, %function
_init_tail:
	bl main
