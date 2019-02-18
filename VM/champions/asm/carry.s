.name "carry"
.comment "carry"

ici:
st r1,511
zjmp %:ici
ld %0,r1
ld %0,r10
ld %0,r11
ld %10,r2
zjmp %:ici
st r1,511
zjmp %:ici
st r0,511
zjmp %:ici
st r2,0
zjmp %:ici
sti r1,%510,%1
zjmp %:ici
sti r2,%0,%0
zjmp %:ici
sti r0,%0,%0
zjmp %:ici
sti r1,%0,%0
zjmp %:ici
ld %1,r0
zjmp %:suite
ld %1,r1
zjmp %:suite
ld %0,r1			#modif carry
zjmp %:suite
live %16
sti r2,%510,%1
suite:
and %1,%1,r3
ldi %0,%0,r3
zjmp %:suite
ldi %1,%1,r1
zjmp %:suite
ldi %1,%1,r0
zjmp %:suite
ldi 511,%0,r3
zjmp %:suite
ldi %511,%0,r3
st r3,511
zjmp %:suite
add r1,r3,r10
zjmp %:suite
add r10,r11,r12
zjmp %:suite
ld %0,r10
ld %0,r11
add r10,r11,r12
zjmp %:suite			#modif carry
