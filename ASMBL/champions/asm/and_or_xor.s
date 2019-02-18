.name "and or xor"
.comment "and or xor"

ici:
ld %2,r2
ld %0,r3
ld %4,r4
and r2,r2,r5
ldi r5, %0, r8
and r2,%10,r5
ldi r5, %0, r8
and r2,512,r5
ldi r5, %0, r8
and r2,514,r5
ldi r5, %0, r8
and r2,510,r5
ldi r5, %0, r8
and %10,r4,r5
ldi r5, %0, r8
and %10,%10,r5
ldi r5, %0, r8
and %10,512,r5
ldi r5, %0, r8
and %10,518,r5
ldi r5, %0, r8
and 518,r4,r5
ldi r5, %0, r8
and 518,%10,r5
ldi r5, %0, r8
and 518,20,r5
ldi r5, %0, r8
and r16,r16,r16
ldi r16, %0, r8
or r2,r2,r5
ldi r5, %0, r8
or r2,%10,r5
ldi r5, %0, r8
or r2,512,r5
ldi r5, %0, r8
or r2,514,r5
ldi r5, %0, r8
or r2,510,r5
ldi r5, %0, r8
or %10,r4,r5
ldi r5, %0, r8
or %10,%10,r5
ldi r5, %0, r8
or %10,512,r5
ldi r5, %0, r8
or %10,518,r5
ldi r5, %0, r8
or 518,r4,r5
ldi r5, %0, r8
or 518,%10,r5
ldi r5, %0, r8
or 518,20,r5
ldi r5, %0, r8
xor r2,r2,r5
ldi r5, %0, r8
xor r2,%10,r5
ldi r5, %0, r8
xor r2,512,r5
ldi r5, %0, r8
xor r2,514,r5
ldi r5, %0, r8
xor r2,510,r5
ldi r5, %0, r8
xor %10,r4,r5
ldi r5, %0, r8
xor %10,%10,r5
ldi r5, %0, r8
xor %10,512,r5
ldi r5, %0, r8
xor %10,518,r5
ldi r5, %0, r8
xor 518,r4,r5
ldi r5, %0, r8
xor 518,%10,r5
ldi r5, %0, r8
xor 518,20,r5
ldi r5, %0, r8
