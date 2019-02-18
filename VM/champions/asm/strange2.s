.name "strange2"
.comment "strange 2 exe order"

ld %57672459,r2
ld %50556929,r3
ld %1879245057,r4
sti r2,%:target,%0
sti r3,%:target,%4
ld %0,r10
fork %:queu
zjmp %:ap_live
queu:
live %0
live %0
live %0
live %0
live %0
target:
and %50,r10,r10
live:
live %723712
ap_live:
and %0,%0,r10
ld %0,r10
sti r4,%:live,%-3
