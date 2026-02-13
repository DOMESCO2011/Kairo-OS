[bits 32]
extern divide_by_zero_handler
global isr0
global idt_load

; Exception 0: Divide by Zero
isr0:
    pusha               ; Minden regiszter mentése (EAX, EBX, stb.)
    call divide_by_zero_handler
    popa                ; Regiszterek visszaállítása
    iret                ; Visszatérés a megszakításból (fontos: nem ret!)

; Az IDT pointer betöltése a processzorba
idt_load:
    mov edx, [esp + 4]  ; C-ből kapott idtp címe
    lidt [edx]          ; Load IDT
    ret
