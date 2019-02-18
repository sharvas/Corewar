.name "blip"
.comment "blop"

ici:
ldi 3,%4,r3
#st r3,65520
ldi %65530,%2,r3
ldi %500,%2,r3
ldi %1000,%2,r3
st r3,1000
ldi r3,%5,r3
st r3,1000
ldi %:ici,%0,r3
st r3,1000
ldi 3,%5,r0
ld 10, r3 
