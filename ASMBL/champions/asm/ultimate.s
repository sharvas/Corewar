.name "utlimate"
.comment "utlimate"

debut:
live %4
ld 1000,r4
ld %:debut,r4
ld %-512,r4
add r1, r2, r3
sub r1, r2, r3
and r1, r2, r3
and r1, %10, r3
and r1, 10, r3
and %10, r2, r3
and %10, 1, r3
and %10, %1, r3
and 10, r2, r3
and 10, %10, r3
and 10, 1, r3
or r1, r2, r3
or r1, %10, r3
or r1, 10, r3
or %10, r2, r3
or %10, 1, r3
or %10, %1, r3
or 10, r2, r3
or 10, %10, r3
or 10, 1, r3
xor r1, r2, r3
xor r1, %10, r3
xor r1, 10, r3
xor %10, r2, r3
xor %10, 1, r3
xor %10, %1, r3
xor 10, r2, r3
xor 10, %10, r3
xor 10, 1, r3
zjmp %3
ldi r1, r2, r3
ldi r1, %10, r3
ldi %10, r2, r3
ldi %10, %1, r3
ldi 10, r2, r3
ldi 10, %10, r3
fork %1000
lld 10,r2
lld %10,r2
lldi r1, r2, r3
lldi r1, %10, r3
lldi %10, r2, r3
lldi %10, %1, r3
lldi 10, r2, r3
lldi 10, %10, r3
lfork %1000
live %3
aff r1
st r2,r6
st r2,-15
sti r0,r1,r3
sti r2,r1,r3
sti r2,%1,r3
sti r2,%1,%12
and %0,%0,r2
zjmp %3
sti r2,r6,%-100
sti r2,500,%-512
sti r2,500,r6
