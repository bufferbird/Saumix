
CC = aarch64-none-elf-gcc   // unfinish, dont ask 
LD = aarch64-none-elf-ld
OBJCOPY = aarch64-none-elf-objcopy

CFLAGS = -Wall -O2 -ffreestanding -nostdlib -nostartfiles

OBJ_FILES = boot.o kernel.o scheduler.o hardware/uart.o

all: kernel8.img

kernel8.img: kernel.elf
	$(OBJCOPY) -O binary kernel.elf kernel8.img

kernel.elf: $(OBJ_FILES)
	$(LD) -T linker.ld $(OBJ_FILES) -o kernel.elf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@						
clean:
	rm *.o *.elf *.img
