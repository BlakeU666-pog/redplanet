#include "../../include/redplanet.h"
#include "../../include/display.h"
#include <stdint.h>
#include <stddef.h>

int VGA_HEIGHT = 25;
int VGA_WIDTH = 80;

int x;
int y;

#pragma region __CURSOR_HANDLING

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
}

#pragma endregion __CURSOR_HANDLING

#pragma region __BASIC_PRINTING

void putch(char c) {
	switch (c) {
		case '\n':
			x = 0;
			y++;
		break;

		case '\0': return;

		case ' ':
			x++;
		break;

		default:
		{
			uint16_t *where = (uint16_t*) 0xB8000 + (y * VGA_WIDTH + x);
			*where = c | (0x0F << 8);

			x++;
		}
		break;
	}

	//If cursor has reached max width
	if (x == VGA_WIDTH) {
		x = 0;
		y++;
	}

	set_cursor_p(x, y);
}

void print(const char *str) {
	while (*str != 0) {
		putch(*str++);
	}
}

#pragma endregion __BASIC_PRINTING

void clear_screen(void) {
    for (size_t i; i < VGA_WIDTH; i++) {
        for (size_t j; j < VGA_HEIGHT; j++) {
            putch(' ');
        }
    }
}

void init_display(void) {
    print("Initializing display\n");

    int x = 0;
    int y = 0;

    enable_cursor(0,0); //Enables cursor, just in case if the user would change GRUB settings .
                        //GRUB automatically enables cursor if GRUB_TIMEOUT is greater than 0.
    set_cursor_p(x,y);
}
