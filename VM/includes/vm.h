#ifndef VM_H
# define VM_H

# include "../../op.h"
# include "../libft/ft_printf/ft_printf.h"
# include <fcntl.h>

# define FILE_SIZE 		(PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE)

# define LIGHT		"\x1B[47;1;31m"
# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define BRED		"\x1B[41m"
# define BGREEN		"\x1B[42m"
# define BYELLOW	"\x1b[43m"
# define BBLUE		"\x1b[44m"
# define RESET		"\x1B[0m"

typedef struct			s_process
{
	int					index;
	int					reg[17];
	int					duration;
	int					carry;
	int					alive;
	unsigned char		champ;
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
	struct s_champ		champ[5];
	int					champ_count;
	struct s_process	*process;
	int					flag_cp;
}						t_game;

/*
**		game.c
*/
void					ft_game(t_game *game);

t_op					ft_get_op(int index);

unsigned int			ft_reverse_bytes(void *ptr, int size);
unsigned int			ft_get_bytes(void *ptr, int size);

void					print_arena_color(t_game *game);

void					op_live(t_game *game, t_process *process);
void					op_ld(t_game *game, t_process *process);
void					op_st(t_game *game, t_process *process);
void					op_add(t_game *game, t_process *process);
void					op_sub(t_game *game, t_process *process);
void					op_and(t_game *game, t_process *process);
void					op_or(t_game *game, t_process *process);
void					op_xor(t_game *game, t_process *process);
void					op_zjmp(t_game *game, t_process *process);
void					op_ldi(t_game *game, t_process *process);
void					op_sti(t_game *game, t_process *process);

void					op_lld(t_process *process);
void					op_lldi(t_process *process);
void					op_lfork(t_process *process);
void					op_aff(t_process *process);
 
#endif