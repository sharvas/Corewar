.name "exe order"
.comment "test ordre execution process"

ld %50397184,r2
fork %:st
sti r2,%:dest,%0
st:
st r2,17
zjmp %:dest
dest:
sti r1,r2,r2
