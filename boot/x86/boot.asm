MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
FLAGS    equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)
 
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
 
section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:
 
section .text
global _start:function (_start.end - _start)

gdtr	DW 0
	DD 0

setGdt:
   MOV   AX, [esp + 4]
   MOV   [gdtr], AX
   MOV   EAX, [ESP + 8]
   ADD   EAX, [ESP + 12]
   MOV   [gdtr + 2], EAX
   LGDT  [gdtr]
   RET

_start:
	call setGdt
	mov esp, stack_top
	extern kernel_main
	call kernel_main
 
	cli
.hang:	hlt
	jmp .hang
.end:
