section .text
    extern read_public_key

    global encrypt

encrypt:
    push rbp
    mov rbp, rsp

exit:
    leave 
    ret
    
