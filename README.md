# Corewar

> [Core War](https://en.wikipedia.org/wiki/Core_War) is a 1984 programming game created by D. G. Jones and A. K. Dewdney in which two or more battle programs (called "warriors") compete for control of a virtual computer. These battle programs are written in an abstract assembly language called Redcode.

The goal of this project was to write a `corewar` (virtual machine), an `asm` (assembler) and a `champion` (fighting program).

The `champion` is written in an assembly syntax. With the `asm` (assembler) it is converted into a binary file. And then loaded into the `corewar` (virtual machine) as a process with other 'warriors' (battle programs). Their bytecode is loaded into the circular virtual memory.

![corewar](https://github.com/sharvas/corewar/raw/master/resources/corewar.gif)

In virtual arena `champions` battle with various strategies to win. `corewar` will end when `cycle_to_die` gets bellow 0 or when all the processes have died. The winner is the last `champion` to have been reported alive.

Some of the strategies are:
* Aiming to execute `live` last.
* Executing a `fork` to create more processes who work on behalf of the champion.
* Modify enemy `champion` bytecode so that opponent processes work in your favour.
* Overwrite enemy `champion` bytecode, so they are unable to execute live.

The `champion` in an assembly language:
```assembly
.name     "the_best_player_around_the_whole_universe"
.comment  "(anti-zork)"
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
```

And the bytecode, compiled with `asm`, that gets loaded into the `corewar`:
```console
$> hexdump -C champion/the_best_player_around_the_whole_universe.cor
00000000  00 ea 83 f3 74 68 65 5f  62 65 73 74 5f 70 6c 61  |....the_best_pla|
00000010  79 65 72 5f 61 72 6f 75  6e 64 5f 74 68 65 5f 77  |yer_around_the_w|
00000020  68 6f 6c 65 5f 75 6e 69  76 65 72 73 65 00 00 00  |hole_universe...|
00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000080  00 00 00 00 00 00 00 00  00 00 00 44 28 61 6e 74  |...........D(ant|
00000090  69 2d 7a 6f 72 6b 29 0a  00 00 00 00 00 00 00 00  |i-zork).........|
000000a0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000890  02 90 03 80 00 00 02 0b  68 01 00 0e 00 01 0b 68  |........h......h|
000008a0  01 00 14 00 01 01 00 00  00 2b 09 ff fb 04 54 02  |.........+....T.|
000008b0  03 03 01 00 00 00 01 0b  68 03 00 07 00 01 0f 04  |........h.......|
000008c0  d6 01 00 00 00 00 0c ff  e7 06 64 01 00 00 00 00  |..........d.....|
000008d0  01 09 ff d4                                       |....|
000008d4
```

The program cannot leak. All errors must be handled carefully. In no way can the program quit in an unexpected manner (Segmentation fault, bus error, double free, etc). Allowed functions for the mandatory part are `open`, `read`, `lseek`, `write`, `close`, `malloc`, `realloc`, `free`, `perror`, `strerror` and `exit`.

## Usage

Run `make` to compile `asm` and `corewar`.

### asm

```console
$> ./asm
Usage : ./asm <sourcefile.s>
```
```console
$> ./asm -o
Usage : ./asm -c/o <dest> <sourcefile.s>
```

For the basic functionality `asm` has to take as an argument a `champion` with a '.s' file extension. If the `champion` is valid, it must be compiled. The compiled '.cor' binary must be placed in the same directory and with the same filename as the assembly file.

As a bonus, `asm` can compile multiple assembley files with one run. With the flag `-o` the destination folder can be specified. And the flag `-c` removes the filesize limit. Also `asm` displays detailed error messages displaying line and collumn of the error in the assembley file.

### corewar

```console
$> ./corewar

usage:	./corewar [-dump nbr_cycles] [-i] [-a] [-op] [-arg] [-v [speed (1-100)]] [-w nbr_cycles] [-cp] [-e] [[-n number] champion1.cor] ...

	[-dump nbr_cycles] at the end of nbr_cycles of executions, dump the memory on the standard output and quit
	[-i] print introduction of contestants
	[-a] don't print live operations
	[-op] print operations excecuted, for debugging
	[-arg] print argument sizes, for debugging
	[-v [speed (1-100)]] vizualizer, optional speed between 1 (slow) and 100 (fast). (max 4 champions)
	[-w nbr_cycles] wait nbr_cycles before starting vizualizer
	[-cp] in visualizer color process pointers according to which champion is the parent
	[-e] print "Game ended at cycle count: (cycle_count)"
	[-n number] sets the number of the next player

```

There are two big groups of `corewar` functionality. The debugging mode and the visualiser.

`corewar` degugging works with the flag `-op` that prints out each executed operation and the argument values. The flag `-arg` also displays values extracted from the coding byte.

`corewar` visualiser allows to display the game in any state. With the flag `-w` the game can be started at a certain cycle and with the flag `-dump` stopped at a specified cycle. Flag `-e` allows to find out the cycle when the game ends.

The game also has audio effects when the processes gets killed with every check. And processes can be coloured in the colours inherited from the champions.

### champion

The champion (***the_best_player_around_the_whole_universe***) was written to always win agains the `zork`. It does so by overwriting `zork` program with the name of itself, `fork`'ing itself and calling itself `alive` in its own program and the zombie `zork`.

```assembly
.name "the_best_player_around_the_whole_universe"
.comment"(anti-zork)"
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
```
VS
```assembly
.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live
```


![champion](https://github.com/sharvas/corewar/raw/master/resources/champion.gif)

The project was completed in a team of four with [@erli](https://github.com/dracoeric) @pmasson and [@dfinnis](https://github.com/dfinnis).
