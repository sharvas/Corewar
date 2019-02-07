#ifndef VM_H
# define VM_H

# include "../../op.h"
# include "../libft/ft_printf/ft_printf.h"
# include <fcntl.h>

# define FILE_SIZE 		(PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE)

typedef struct			s_process
{
	unsigned char		*current;//process
	int					index;
	unsigned char		reg[16];
	int					duration;
	int					carry;
	int					alive;
	struct s_process	*next;
}						t_process;

typedef struct			s_champ
{
	struct header_s		header;
	int					nbr;
	int			    	alive;
}						t_champ;

// typedef struct		s_arena
// {
// 	unsigned char		value;
// 	int					champ;
// 	int					ptr;
// }					t_arena;

typedef struct			s_game
{
	unsigned char		arena[MEM_SIZE];
	int					dump;//cycle_to_dump;
	int					cycle_to_die;
	int					cycle;
	int					alive;
	struct s_champ		champ[4];
	struct s_process	*process;
}						t_game;

/*
**		game.c
*/
void	ft_game(t_game *game);

t_op	*ft_get_op(void);

long long	ft_reverse_bytes(unsigned char *ptr, int size);

#endif