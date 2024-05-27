section .text
    global decrypt

decrypt:
    push rbp
    mov rbp, rsp

exit:
    leave 
    ret
    