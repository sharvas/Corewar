.name "strange"
.comment "strange exe order"

ld %57672459,r2
ld %50556929,r3
ld %1879245057,r4
sti r2,%:live,%-8
sti r3,%:live,%-4
fork %:ap_live
ld %0,r10
ld %0,r10
zjmp %10
ld 500,r1
ld 0,r0
ld 500,r1
live:
live %723712
ap_live:
and %0,%0,r10
ld %0,r10
sti r4,%:live,%-3
