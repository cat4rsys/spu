jmp main

dup:
pop ax
push ax
push ax
ret

factorial:
call dup
push 2
jb end
call dup
push 1
sub
call factorial
mul
ret

end:
ret

main:
in
call factorial
out
hlt