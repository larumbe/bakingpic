	.section .init
	
.global _start
_start:
    mov         sp, #0x8000         @; set up the stack pointer
	b _main

	.section .text

_main:
	b notmain

	.section .data
	


