global f1, f2, f3, df1, df2, df3
section .data
    const2 dd 14
    const3 dd 6
section .text
f1: ;y = ln x
    push ebp
    mov ebp, esp
    sub esp, 8
    
    ;ln x = ln 2 * log2(x)
    finit
    fldln2
    fld qword[ebp + 8]
    fyl2x
    
    leave
    ret

f2: ;y = -2x + 14
    push ebp
    mov ebp, esp
    sub esp, 8
    
    ;y = (x + x) * (-1) + 14
    finit
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    faddp
    fchs
    fild dword[const2]
    faddp
    
    leave
    ret

f3: ;y = 1 / (2 - x) + 6
    push ebp
    mov ebp, esp
    sub esp, 8
    
    finit
    fld1
    fld1
    fld1
    faddp
    fld qword[ebp + 8]
    fsubp
    fdivp st1, st0
    fild dword[const3]
    faddp
    
    leave
    ret

df1: ;y = 1 / x
    push ebp
    mov ebp, esp
    sub esp, 8
    
    finit
    fld1
    fld qword[ebp + 8]
    fdivp st1, st0
    
    leave
    ret

df2: ;y = -2
    push ebp
    mov ebp, esp
    sub esp, 8
    
    finit
    fld1
    fld1
    faddp
    fchs
    
    leave
    ret

df3: ;y = 1 / (2 - x) / (2 - x)
    push ebp
    mov ebp, esp
    sub esp, 8
    
    finit
    fld1
    fld1
    fld1
    faddp
    fld qword[ebp + 8]
    fsubp
    fdivp st1, st0
    
    fld1
    fld1
    faddp
    fld qword[ebp + 8]
    fsubp
    fdivp st1, st0
    
    leave
    ret