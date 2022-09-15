#include <stdint.h>
#include <include/string.h>
#include <boot/x86/asm.h>
#include <boot/x86/pic/pic.h>
#include <drivers/display/fb/fb.h>
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

static uint8_t shift_state;

char *keyboard_readinput(void) {
	char *buf = 0;
	int pos = 0;
	char c = 0;
	do {
		if (inb(0x60)!=c) {
			c = inb(0x60);

			if (inb(0x60) == 8) {
				if (pos == 0) return;
				buf[strlen(buf)-1] = '\0';
				pos--;
			}
			pos++;
			kputch(map_us[c]);
		}
	} while (c != 28);
	return *buf;
}

void init_keyboard() {
	kprint("Initializing PS/2 keyboard driver\n");
	shift_state = 0;
	PIC_sendEOI(33);
}
