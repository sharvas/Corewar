.name "lldi"
.comment "lldi"

lldi 2048,%0,r3
sti r3,%-510,%-1
lldi 1024,%0,r3
sti r3,%-510,%-1
lldi %1024,%0,r3
sti r3,%-510,%-1
ldi 1024,%0,r3
sti r3,%-510,%-1
