section .text
    extern _fun_modulo
    global _fun_euklides

_fun_euklides:
    push rbp
    mov rbp, rsp

_euklides_loop:
    cmp rsi, 0
    je _end 
    jne _calc
    
_calc:
    call _fun_modulo
    push rsi    
    mov rsi, rax
    pop rdi
    jmp _euklides_loop

_end:
    mov rax, rdi
    leave
    ret
