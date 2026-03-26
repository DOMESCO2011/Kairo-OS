[BITS 32]
global gdt_flush    ; Lehetővé teszi a C kód számára a hívást

section .text
gdt_flush:
    mov eax, [esp + 4]  ; Az első paraméter (a gp címe) lekérése a stackről
    lgdt [eax]          ; A GDT betöltése

    ; A szegmensregiszterek frissítése
    mov ax, 0x10        ; 0x10 a Kernel Data szegmens (2. bejegyzés * 8)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Távoli ugrás a Code szegmensbe (0x08), hogy frissítsük a CS-t
    jmp 0x08:.flush
.flush:
    ret