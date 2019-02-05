#ifndef VM_H
# define VM_H

# include "../../op.h"
# include "../libft/ft_printf/ft_printf.h"

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
	int					duration;
	unsigned char		reg[16];
	int					carry;
	int					alive;
}						t_process;

typedef struct			s_champ
{
	int					nbr;
	char				name[PROG_NAME_LENGTH];
	char				comment[COMMENT_LENGTH];
	struct s_process	*process;
	int			    	alive;
}						t_champ;

typedef struct			s_game
{
	int					dump;
	struct s_champ		champ[4];
}						t_game;

#endif
