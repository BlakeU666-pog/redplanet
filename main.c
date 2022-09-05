#include <drivers/display/display.h>
#include <drivers/keyboard/kbd.h>
#include <boot/x86/idt/idt.h>
#include <boot/x86/pic/pic.h>

void kernel_main() {
	clear_screen();
	print("Loading Red Planet\n");
	
	init_idt();
	init_PIC();
	init_keyboard();

	while(1)
		keyboard_get_key();
}
