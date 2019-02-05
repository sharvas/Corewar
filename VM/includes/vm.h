#ifndef VM_H
# define VM_H

# include "../../op.h"
# include "../libft/ft_printf/ft_printf.h"

typedef struct			s_champ
{
	char		    	*name;
	char				*comment;
	struct s_process	*process;
	int			    	alive;
}						t_champ;

typedef struct			s_process
{
	unsigned char		*current;
	int					duration;
	unsigned char		reg[16];
	int					carry;
}						t_process;

#endif
