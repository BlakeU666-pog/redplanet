#include <boot/x86/asm.h>
#include <drivers/display/display.h>
#include <stdint.h>
#include <stddef.h>

int VGA_HEIGHT = 25;
int VGA_WIDTH = 80;

int cx;
int cy;

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void set_cursor_p(int x, int y)
{
	uint16_t pos = (y * 80 + x); //Calculate position on screen based on given coordinates

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
	
	cx = x;
	cy = y;
}

void putch(char c) {
	switch (c) {
		case '\n':
			cx = 0;
			cy++;
		break;

		case '\0': return;

		case ' ':
			cx++;
		break;

		case '\t':
			cx = cx + 8;
		break;

		case '\b':
			cx--;
			uint16_t *where = (uint16_t*) 0xB8000 + (cy * VGA_WIDTH + cx);
			*where = ' ' | (0x0F << 8);
		break;

		default:
		{
			uint16_t *where = (uint16_t*) 0xB8000 + (cy * VGA_WIDTH + cx);
			*where = c | (0x0F << 8);

			cx++;
		}
		break;
	}

	//If cursor has reached max width
	if (cx == VGA_WIDTH) {
		cx = 0;
		cy++;
	}

	set_cursor_p(cx, cy);
}

void print(const char *str) {
	while (*str != 0) {
		putch(*str++);
	}
}

void clear_screen() {
	uint16_t* vidmem = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < 25; y++) {
		for (size_t x = 0; x < 80; x++) {
			const size_t index = y * 80 + x;
			vidmem[index] = ' ' | (0x0F << 8);
		}
	}
	set_cursor_p(0,0);
}
