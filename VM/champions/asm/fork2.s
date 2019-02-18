.name "fork2"
.comment "fork2"

fork %65530
live %2
fork %:la
la:
sti r1,500,%500
sti r1,500,%500
live %2
fork %:la
