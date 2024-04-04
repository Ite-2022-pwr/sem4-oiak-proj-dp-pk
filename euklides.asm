section .text
    extern _fun_modulo
    global _fun_euklides

_fun_euklides:
    cmp rsi, 0
    je _end 
    jne _calc
    
_calc:
    call _fun_modulo
    push rsi    
    mov rsi, rax
    pop rdi
    jmp _fun_euklides

_end:
    mov rax, rdi
    leave
    ret
