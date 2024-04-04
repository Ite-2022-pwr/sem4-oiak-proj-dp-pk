; POWER FUNCTION
; takes base in RDI and exponent RSI 
; returns result in RAX

section .text
global calculate_power

calculate_power:
    ; Function Prologue
    push rbp
    mov rbp, rsp

    ; Arguments:
    mov rdx, 1        ; Clear rdx (result)

power_loop:
    cmp rsi, 0                     ; Compare exponent with 0
    je power_end                   ; If exponent is 0, end loop
    
    ; Multiply result by base
    imul rdx, rdi                  ; rdx = rdx * rdi
    
    ; Decrement exponent
    dec rsi
    
    ; Repeat loop
    jmp power_loop

power_end:
    ; Return the result
    mov rax, rdx

exit:
    ; Function Epilogue
    leave
    ret
