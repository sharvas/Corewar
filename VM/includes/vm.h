#ifndef VM_H
# define VM_H

# include "../../op.h"
# include "../libft/ft_printf/ft_printf.h"

s_struct	s_champ
{
	char			*name;
	unsigned char	reg[16];
	t_process		*process;
	int				alive;
}			t_champ;

s_struct	s_process;
{
	unsigned char	*current;
	int				duration;
	
}

#endif