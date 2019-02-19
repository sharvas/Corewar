.name "the_best_player_around_the_whole_universe"
.comment"(anti-zork)
"
		ld	%58720256, r2
		sti r1, %:live, %1
		sti r1, %:live2, %1
live:	live	%43
		zjmp %:live
add:	add r2, r3, r3
live2:	live %1 
		sti r3, %:lfork, %1
lfork:	lfork %1238
		live %0
		fork %:add
		and r1, %0, r1
		zjmp %:live
	
