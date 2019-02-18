.name "fork"
.comment "fork"

fork %:la
la:
sti r1,500,%500
sti r1,500,%500
live %2
fork %:la
