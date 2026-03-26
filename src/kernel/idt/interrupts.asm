; src/kernel/idt/interrupts.asm

; --- EZEK A SOROK HIÁNYOZNAK VALÓSZÍNŰLEG ---
global idt_load
global isr0
global syscall_handler_asm
; -------------------------------------------

extern syscall_handler ; Ez a C függvény, amit meghívunk

idt_load:
    mov eax, [esp + 4]
    lidt [eax]
    ret

isr0:
    pushad
    ; ... hívás a handlerre ...
    popad
    iretd

syscall_handler_asm:
    pushad              ; Regiszterek mentése
    
    ; Paraméterek átadása a C függvénynek (EBX = arg1, EAX = syscall_num)
    push ebx            
    push eax            
    
    call syscall_handler
    
    add esp, 8          ; Stack tisztítása
    popad               ; Regiszterek visszaállítása
    iretd