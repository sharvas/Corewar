#ifndef VM_H
# define VM_H

# include "../../op.h"
# include "../libft/ft_printf/ft_printf.h"

# include <fcntl.h>

typedef struct			s_champ
{
	int					nbr;
	char		    	*name;
	char				*comment;
	struct s_process	*process;//
	int			    	alive;
}						t_champ;

typedef struct			s_game
{
	int					dump;
	struct s_champ		champ[4];
	// struct s_process	process;
}						t_game;

typedef struct			s_process
{
	unsigned char		*current;
	int					duration;
	unsigned char		reg[16];
	// unsigned char		*pc;//
	int					carry;
	int					alive;

}						t_process;

#endif
