; function that performs extended euklides
; Arguments: a - RDI, m - RSI
; Results: d - rax, y - RBX, x - RCX
;

section .text
    extern _fun_modulo
    global _fun_extended_euklides

_fun_extended_euklides:
    push rbp
    mov rbp, rsp

    mov rbx, 1      ; iterator i

_loop:
    ; no inversion, jump to end
    cmp rbx, rsi
    je _no_inversion

    call _fun_modulo
    push rdi
    push rax

    mov rdi, rbx
    call _fun_modulo

    pop rcx             ; first mod value in rcx
    imul rax, rcx       ; aMOd * xMod, result in rax

    mov rdi, rax
    call _fun_modulo
    
    pop rdi
    cmp rax, 1
    jne _continue_loop

    mov rax, rbx
    jmp _end_euklides

_continue_loop:
    inc rbx
    jmp _loop

_no_inversion:
    mov rax, -1

_end_euklides:
    pop rbp
    ret
