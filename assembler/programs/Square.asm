jmp main
discrim:
push bx
push bx
mul
push 4
push ax
mul
push cx
mul
sub
pop dx
ret
main:
in
in
in
pop cx
pop bx
pop ax
push ax
push 0
je line
call discrim
push dx
push 0
jb zero
push dx
push 0
je one
jmp two
line:
push bx
push 0
je const
push 1
out
push cx
push bx
div
push -1
mul
out
hlt
const:
push cx
push 0
je inf
jmp zero
hlt
inf:
push 3
out
hlt
zero:
push 0
out
hlt
one:
push 1
out
push bx
push 2
push ax
mul
div
push -1
mul
out
hlt
two:
push 2
out
push bx
push 2
push ax
mul
div
push -1
mul
pop ex
push dx
sqrt
push 2
push ax
mul
div
pop dx
push ex
push dx
sub
out
push ex
push dx
add
out
hlt
