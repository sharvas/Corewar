.name "blip"
.comment "blop"

#REG = 1
#DIR = 2
#IND = 3

ici:
live %:ici
ld %15, r12
aff r12
lfork %12
lldi r1, %12, r2
lld 12, r1
fork %12


#ld 1,r5
#ld %:ici,r5
sti r5,%:ici,%0
and %1,%0,r3
zjmp %:ici
#zjmp %65499
