section .data
    base        equ 5              ; Define base as a constant
    exponent    equ 7               ; Define exponent as a constant
    
section .bss
    result resq 64

section .text
    global _start

_start:
    ; Function Prologue
    push rbp
    mov rbp, rsp

    ; Initialize result to 1
    mov rax, base                  ; Load base into rax
    mov rcx, exponent              ; Load exponent into rcx
    mov rdx, 1                     ; Clear rdx (result)

power_loop:
    cmp rcx, 0                     ; Compare exponent with 0
    je power_end                   ; If exponent is 0, end loop
    
    ; Multiply result by base
    imul rdx, rax                  ; rdx = rdx * rax
    
    ; Decrement exponent
    dec rcx
    
    ; Repeat loop
    jmp power_loop

power_end:
    ; Store the result
    mov [result], rdx

    ; Write the result to stdout
    mov rax, 1
    mov rdi, 1                     ; File descriptor for stdout
    mov rsi, [result]              ; Load the address of result into rsi
    mov rdx, 64                     ; Length of data to write (8 bytes for quadword)       ; syscall number for sys_write
    syscall                        ; invoke sys_write

    ; Exit program
    mov rax, 60                    ; syscall number for exit
    mov rdi, 0                     ; exit code 0
    syscall                        ; invoke syscall to exit
