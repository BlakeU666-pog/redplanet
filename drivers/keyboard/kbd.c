#include <stdint.h>
#include <boot/x86/asm.h>
#include <boot/x86/pic/pic.h>
#include <drivers/display/display.h>
#include "kbd.h"

char map_us[0x100] = {
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

char map_us_shift[0x100] = {
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', 0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', 0, '*', 0, ' '
};

unsigned char lastkey;
static uint8_t shift_state;

char keyboard_get_key() {
	volatile unsigned char scancode = inb(0x60);
	if (scancode == lastkey)
		return;

	if (scancode == 0x2A) { //Left shift pressed
		shift_state = 1;
	} else if (scancode == 0xAA) { //Left shift released
		shift_state = 0;
	}

	lastkey = scancode;
	if (shift_state == 0) {
		putch(map_us[scancode]);
	} else if (shift_state == 1) {
		putch(map_us_shift[scancode]);
	}
}

void init_keyboard() {
	print("Initializing PS/2 keyboard driver\n");
	shift_state = 0;
	PIC_sendEOI(33);
}	
