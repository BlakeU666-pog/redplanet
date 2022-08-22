.PHONY: default
default: link

CC=i686-elf-gcc
AS=nasm
LD=i686-elf-ld
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
CFILES=$(shell find . -name "*.c")
OBJS=$(CFILES:.c=.o) boot/x86/boot.o

boot/x86/boot.o: boot/x86/boot.asm
	@$(AS) $< -felf32 -o $@

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

link: $(OBJS)
	@$(LD) -nostdlib -O2 -Tboot/x86/linker.ld $^ -o redplanet.bin

clean:
	@rm -f $(OBJS)

makeiso:
	$(shell cp redplanet.bin iso/boot)
	@grub-mkrescue -o redplanet.iso iso
