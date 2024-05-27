section .text
    global encrypt

encrypt:
    push rbp
    mov rbp, rsp

exit:
    leave 
    ret
    