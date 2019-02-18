.name "blip"
.comment "blop"

ici:
ldi %:ici,%1,r5
sti r3,%:ici,%1
sti r5,%:ici,%2
and %1,%0,r3
zjmp %:ici
