# Fordító és alapvető flag-ek
CC = gcc
AS = nasm
LD = ld
# Hozzáadtuk: -mno-sse -mno-sse2 -mno-mmx -mno-80387
CFLAGS = -m32 -ffreestanding -nostdlib -fno-stack-protector -fno-pie \
         -mno-sse -mno-sse2 -mno-mmx -mno-80387 \
         -Isrc/kernel -Isrc/include \
         -Isrc/kairopak/kp-manager \
         -Isrc/kairopak/kp-recorder \
         -Isrc/kairopak/kp-link

ASFLAGS = -f elf32
LDFLAGS = -m elf_i386

# Kimeneti könyvtárak
BIN_DIR = bin/kernel_obj
OUTPUT = bin/kairos-kernel

# Forrásfájlok automatikus keresése (minden .c és .asm az src alatt)
C_SOURCES = $(shell find src -name "*.c")
ASM_SOURCES = $(shell find src -name "*.asm")

# Objektum fájlok generálása (leképezzük az src/ útvonalat a bin/kernel_obj/ útvonalra)
C_OBJS = $(patsubst src/%.c, $(BIN_DIR)/%.o, $(C_SOURCES))
ASM_OBJS = $(patsubst src/%.asm, $(BIN_DIR)/%.o, $(ASM_SOURCES))
OBJS = $(C_OBJS) $(ASM_OBJS)

all: $(OUTPUT)

# A végső kernel linkelése
$(OUTPUT): $(OBJS)
	@mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -T src/kernel/linker.ld -o $(OUTPUT) $(OBJS)

# Általános szabály minden C fájlra (legyen az kernel vagy kairopak)
$(BIN_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Általános szabály minden Assembly fájlra
$(BIN_DIR)/%.o: src/%.asm
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf bin/

run: all
	qemu-system-i386 -kernel $(OUTPUT) -d int,cpu_reset