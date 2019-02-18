.name "fork2"
.comment "fork2"

la:
lfork %65535
live %1
lfork %65536
live %1
lfork %75000
live %1
live %1
lfork %512
live %1
lfork %:la
live %1
lfork %1000
live %1
