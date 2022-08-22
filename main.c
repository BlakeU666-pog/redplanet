#include <drivers/display.h>
#include <drivers/kbd.h>
#include <boot/x86/asm.h>

void kernel_main() {
	clear_screen();
	print("Starting Red Planet...\n");
}