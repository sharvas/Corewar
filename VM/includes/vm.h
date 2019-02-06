#ifndef VM_H
# define VM_H

# include "../../op.h"
# include "../libft/ft_printf/ft_printf.h"

# include <fcntl.h>

# define FILE_SIZE		(PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE)

typedef struct			s_champ
{
	struct header_s		header;
	int					nbr;
	// char		    	name[PROG_NAME_LENGTH];
	// char				comment[COMMENT_LENGTH];
	struct s_process	*process;//
	int			    	alive;
}						t_champ;

typedef struct			s_game
{
	int					dump;
	struct s_champ		champ[4];
	unsigned char   	arena[MEM_SIZE];
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
