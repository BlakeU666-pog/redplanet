#include <drivers/display/fb/fb.h>
#include <drivers/input/keyboard/kbd.h>
#include <boot/x86/idt/idt.h>
#include <boot/x86/pic/pic.h>
#include <include/string.h>

void kernel_main() {
	clear_screen();
	kprint("Loading Red Planet\n");

	init_idt();
	init_PIC();
	init_keyboard();

	while (1) {
		kprint("> ");
		keyboard_readinput();
	}
}
