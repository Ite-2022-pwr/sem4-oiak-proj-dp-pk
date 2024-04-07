; CHECKS IF NUMBER IS PRIME
; argument in rdi
; result in RAX, 1 if prime, 0 if not

section .text
    extern _fun_modulo
    global _fun_prime

_fun_prime:
    push rbp
    mov rbp, rsp

    cmp rdi, 1
    jle _is_not_prime
    cmp rdi, 3
    jle _is_prime

    ;check if number is divisible by 2
    mov rsi, 2
    call _fun_modulo
    cmp rax, 0
    je _is_not_prime
    
    ;check if number is divisible by 3
    mov rsi, 3
    call _fun_modulo
    cmp rax, 0
    je _is_not_prime

    mov rsi, 5  ; i
    mov r8, 2   ; base

_check_loop:
    ; check if i * i > n, if true number is prime
    mov rax, rsi
    imul rax, rax
    cmp rax, rdi
    jnle _is_prime

    ; check modulo(n, i) == 0
    call _fun_modulo
    cmp rax, 0
    je _is_not_prime

    ; check modulo(n, i + 2) == 0
    add rsi, 2
    call _fun_modulo
    cmp rax, 0
    je _is_not_prime

    ; i = i + base
    ; base = 6 - base
    sub rsi, 2
    add rsi, r8
    mov rax, 6
    sub rax, r8
    mov r8, rax

    jmp _check_loop

_is_prime:
    mov rax, 1
    jmp _exit

_is_not_prime:
    mov rax, 0

_exit:
    leave
    ret
