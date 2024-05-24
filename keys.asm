section .data
    key_pub db 'key_pub.txt', 0
    key_priv db 'key_priv.txt', 0

    test_message db 'test!', 0 

section .bss
    first_prime resb 1
    second_prime resb 1
    e resb 1

section .text
    extern write_public_key
    extern write_private_key

    extern _fun_prime
    extern _fun_euklides
    extern _fun_modulo
    ;extern _fun_power
    extern _fun_extended_euklides
    
    global _start

_start:
    push rbp
    mov rbp, rsp

_first_prime_loop:
    mov rax, 318
    mov rdi, first_prime
    mov rsi, 1
    mov rdx, 0
    syscall
    
    mov rdi, [first_prime]    ; check if number is prime, if yes rax == 1, if not rax == 0
    call _fun_prime

    cmp rax, 1
    jne _first_prime_loop

    push rdi

_second_prime_loop:
    mov rax, 318
    mov rdi, second_prime
    mov rsi, 1
    mov rdx, 0
    syscall
    
    mov rdi, [second_prime]    ; check if number is prime, if yes rax == 1, if not rax == 0
    call _fun_prime

    cmp rax, 1
    jne _second_prime_loop

    pop rcx
    mov rbx, [second_prime]

_calculate:
    dec rcx
    dec rbx
    mov rax, rcx
    imul rax, rbx
    
    push rax ; O is on stack

    inc rcx
    inc rbx
    mov rax, rcx
    imul rax, rbx

    push rax ; O, n is on stack

_e_loop:
    mov rax, 318
    mov rdi, e
    mov rsi, 1
    mov rdx, 0
    syscall         ; e is in rax

    mov rcx, [e]    ; move e to rcx

    mov rdi, rcx
    mov rsi, 2
    call _fun_modulo
    mov rcx, rdi

    ; e % 2 == 0
    cmp rax, 0
    je _e_loop

    ; e <= 1
    cmp rcx, 1
    jle _e_loop

    ; e >= n
    pop rbx         ; O is on stack
    cmp rcx, rbx
    push rbx        ; O, n is on stack
    jge _e_loop

    pop rbx             ; O is on stack -> n is in RBX
    pop rdi             ; nothing on stack -> O is in RDI
    mov r8, rdi
    mov rsi, rcx        ; RCX is e -> RSI is e
    call _fun_euklides  ; euklides(RDI[O], RSI[e])

_test1:
    cmp rax, 1
    je _continue_euklides

    push rdi
    push rbx
    jmp _e_loop

_continue_euklides:
    mov r9, rbx
    mov rsi, rcx
    mov rdi, r8 
    call _fun_extended_euklides

; d is in RAX
; e is in RCX
; n is in R9

_write_keys:
    ; write public keys
    mov rdi, rcx
    mov rsi, r9
    call write_public_key
