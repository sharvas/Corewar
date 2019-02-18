.name "blip"
.comment "blop"

ici:
ld %10,r5
ld 1,r5
ld %:ici,r5
sti r5,%:ici,%0
and %1,%0,r3
zjmp %:ici
#zjmp %65499
