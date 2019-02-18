.name "add sub"
.comment "add sub test"

ici:
ld %2,r2
ld %0,r3
ld %4,r4
add r2,r2,r5
sti r5, %500, %0
ldi r5, %0, r8
add r2,r3,r5
sti r5, %500, %0
ldi r5, %0, r8
sub r2,r4,r6
sti r6, %500, %0
ldi r6, %0, r8
sub r5,r1,r6
sti r6, %500, %0
ldi r6, %0, r8
sub r3,r3,r3
sti r3, %500, %0
ldi r3, %0, r8
