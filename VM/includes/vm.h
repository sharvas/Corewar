#ifndef VM_H
# define VM_H

# include "../../op.h"
# include "../libft/ft_printf/ft_printf.h"
# include <fcntl.h>

# define FILE_SIZE		(PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE)

typedef struct			s_op
{
	char				*name;
	int					argc;
	int					*argv;
	int					id;
	int					cycles;
	char				*long_name;
	int					OCP;
	int					carry;
}						t_op;

typedef struct			s_process
{
	unsigned char		*current;
	unsigned char		reg[16];
	int					duration;
	int					carry;
	int					alive;
}						t_process;


typedef struct			s_champ
{
	struct header_s		header;
	int					nbr;
	int			    	alive;
}						t_champ;

typedef struct			s_game
{
	unsigned char		arena[MEM_SIZE];
	int					dump;//cycle_to_dump;
	int					cycle_to_die;
	int					cycle_delta;
	int					max_checks;
	struct s_champ		champ[4];
	struct s_process	*process;
}						t_game;

#endif