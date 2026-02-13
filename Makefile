CC = gcc
CFLAGS = -m32 -ffreestanding -nostdlib -fno-stack-protector -Ikernel
AS = nasm
ASFLAGS = -f elf32
BIN_DIR = bin
KERNEL_DIR = kernel

# Minden .c és .asm fájl megkeresése az összes alkönyvtárban
C_SOURCES = $(shell find $(KERNEL_DIR) -name "*.c")
ASM_SOURCES = $(shell find $(KERNEL_DIR) -name "*.asm")

# Objektum fájlok generálása (megtartva a bin mappán belül is a szerkezetet)
OBJS = $(patsubst $(KERNEL_DIR)/%.c, $(BIN_DIR)/%.o, $(C_SOURCES)) \
       $(patsubst $(KERNEL_DIR)/%.asm, $(BIN_DIR)/%.o, $(ASM_SOURCES))

all: $(BIN_DIR) $(BIN_DIR)/kairos-kernel

# Létrehozzuk a szükséges alkönyvtárakat a bin mappában is
# ... a Makefile eleje változatlan ...

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
	# Ez a verzió biztosan működik Arch Linuxon:
	find $(KERNEL_DIR) -type d -exec sh -c 'mkdir -p "$(BIN_DIR)/$$0"' {} \;

# ... a többi rész változatlan ...

# Assembly fordítás
$(BIN_DIR)/%.o: $(KERNEL_DIR)/%.asm
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

# C fordítás (A -Ikernel miatt a #include "common.h" bárhonnan működik)
$(BIN_DIR)/%.o: $(KERNEL_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Linkelés
$(BIN_DIR)/kairos-kernel: $(OBJS)
	ld -m elf_i386 -T $(KERNEL_DIR)/linker.ld -o $(BIN_DIR)/kairos-kernel $(OBJS)

run: all
	qemu-system-i386 -kernel $(BIN_DIR)/kairos-kernel

clean:
	rm -rf $(BIN_DIR)