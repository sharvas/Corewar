.name "test ocp"
.comment ""

live %0
ld %104, r2
fork %:la
st r2, 3
la:
sti r1, %0, %50
