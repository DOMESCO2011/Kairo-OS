CC = gcc
CFLAGS = -m32 -ffreestanding -nostdlib -fno-stack-protector -I.
AS = nasm
ASFLAGS = -f elf32
BIN_DIR = bin

# Automatikusan megkeres minden .c és .asm fájlt
C_SOURCES = $(wildcard *.c)
ASM_SOURCES = $(wildcard *.asm)

# Objektum fájlok generálása a forrásokból (bin/fájlnév.o formátumban)
OBJS = $(patsubst %.c, $(BIN_DIR)/%.o, $(C_SOURCES)) \
       $(patsubst %.asm, $(BIN_DIR)/%.o, $(ASM_SOURCES))

all: $(BIN_DIR) $(BIN_DIR)/kairos-kernel

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Szabály az assembly fájlokhoz (boot.asm, interrupts.asm)
$(BIN_DIR)/%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

# Szabály a C fájlokhoz (kernel.c, vga.c, idt.c, stb.)
$(BIN_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Összelinkelés
$(BIN_DIR)/kairos-kernel: $(OBJS)
	ld -m elf_i386 -T linker.ld -o $(BIN_DIR)/kairos-kernel $(OBJS)

run: all
	qemu-system-i386 -kernel $(BIN_DIR)/kairos-kernel

clean:
	rm -rf $(BIN_DIR)
