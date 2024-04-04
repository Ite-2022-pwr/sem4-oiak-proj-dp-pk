; MODULO FUNCTION
; takes number in RDI nad devider in RSI

section .text
    global _fun_modulo

_fun_modulo:
    push rbp
    mov rbp, rsp

    cmp rsi, 0
    je _devide_by_zero

    xor rdx, rdx

    mov rax, rdi
    div rsi                 ; devide rax / rsi, rdx = reminder
    jmp _exit

_devide_by_zero:
    mov rax, 0
    leave
    ret

_exit:
    mov rax, rdx            ; move reminder (result of modulo) to rax
    leave
    ret
