#pragma once

#include <stdint.h>
#include <drivers/display/fb/fb.h>
#include <include/string.h>

struct idt_entry {
	unsigned short base_low;
	unsigned short sel;
	unsigned char zero;
	unsigned char flags;
	unsigned short base_high;
} __attribute__((packed));

struct idt_ptr {
	unsigned short limit;
	uintptr_t base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
	idt[num].base_low = (base & 0xFFFF);
	idt[num].base_high = (base >> 16) & 0xFFFF;
	idt[num].sel = sel;
	idt[num].zero = 0;
	idt[num].flags = flags | 0x60;
}

void init_idt() {
	kprint("Setting up IDT\n");
	idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
	idtp.base = (uintptr_t)&idt;
	memset(&idt, 0, sizeof(struct idt_entry) * 256);
}	
