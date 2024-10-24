jmp main
factorial:
push ax
push 1
sub
pop ax
push ax
push 1
jbe end
push ax
mul
call factorial
ret
end:
dump
out
ret
main:
in
pop ax
push ax
call factorial
hlt
