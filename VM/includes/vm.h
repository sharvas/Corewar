#ifndef VM_H
# define VM_H

# include "../../op.h"
# include "../libft/ft_printf/ft_printf.h"
# include <fcntl.h>

# define FILE_SIZE 		(PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE)

typedef struct			s_process
{
	unsigned char		*current;
	int					index;
	unsigned int		reg[16];
	int					duration;
	int					carry;
	int					alive;
	int					champ;
	struct s_process	*next;
}						t_process;

typedef struct			s_champ
{
	struct header_s		header;
	int					start_index;
	unsigned int		nbr;
	int			    	alive;
}						t_champ;

typedef struct			s_game
{
	unsigned char		arena[MEM_SIZE];
	unsigned char		arena_champs[MEM_SIZE];
	int					dump;//cycle_to_dump;
	int					frame_rate;
	int					cycle_to_die;
	int					cycle;
	int					alive;
	struct s_champ		champ[4];
	int					champ_count;
	struct s_process	*process;
}						t_game;

/*
**		game.c
*/
void					ft_game(t_game *game);

t_op					ft_get_op(int index);

unsigned int			ft_reverse_bytes(void *ptr, int size);

void					print_arena_color(t_game *game);

void					op_live(t_game *game, t_process *process);
void					op_ld(t_process *process);
void					op_st(t_process *process);
void					op_add(t_process *process);
void					op_sub(t_process *process);
void					op_and(t_process *process);
void					op_or(t_process *process);
void					op_xor(t_process *process);
void					op_zjmp(t_process *process);
void					op_ldi(t_process *process);
void					op_sti(t_process *process);
 
#endif