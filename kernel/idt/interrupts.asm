[bits 32]
extern divide_by_zero_handler
global isr0
global idt_load

; Exception 0 handling
isr0:
    pusha
    call divide_by_zero_handler
    popa
    iret

; IDT register loading
idt_load:
    mov edx, [esp + 4]
    lidt [edx]
    ret