jmp main

swap:
pop ax
pop bx
push ax
push bx
ret

dup:
pop ax
push ax
push ax
ret

fib:
call dup
push 2
jb end
push 1
sub
call dup
call fib
call swap
push 1
sub
call fib
add
ret

end:
pop ax
push 1
ret

main:
in
call fib
out
hlt