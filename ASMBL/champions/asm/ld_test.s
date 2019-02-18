.name "lld"
.comment "lld"

ici:
ld %10,r5
sti r5,%-510,%1
ld 1,r5
sti r5,%-510,%1
ld %:ici,r5
sti r5,%-510,%1
ld 512,r3
sti r3,%510,%1
ld 1000,r3
sti r3,%510,%1
ld 1000,r3
sti r3,%510,%1
ld 65530,r3
sti r3,%510,%1
ld %0,r0
ld %1,r21
ld %1,r50
