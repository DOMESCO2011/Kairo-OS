bits 32

section .multiboot
    align 4
    dd 0x1BADB002             ; magic number
    dd 0x00                   ; flags
    dd - (0x1BADB002 + 0x00)  ; checksum

section .text
global _start
extern kmain

_start:
    cli                       ; Megszakítások tiltása inicializálás alatt
    mov esp, stack_top        ; A stack mutatót a lefoglalt terület TETEJÉRE állítjuk
    call kmain
    
    ; Ha a kmain valaha visszatérne (nem szabadna):
.halt_loop:
    hlt
    jmp .halt_loop

section .bss
align 16                      ; A stacknek 16 bájtra igazítottnak kell lennie
stack_bottom:
    resb 32768                ; 32 KB helyet foglalunk (8192 helyett)
stack_top:                    ; Ez a cím mutat a 32KB-os blokk végére