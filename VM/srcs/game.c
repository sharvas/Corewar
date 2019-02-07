#include "vm.h"

long long	ft_reverse_bytes(unsigned char *ptr, int size)
{
	long long	ret;
	int			i;

	ret = 0;
	i = 0;
	while (size > 0)
	{
		size--;
		ret |= *(ptr + i) << (size * 8);
		i++;
	}
	return (ret);
}

int	op_live(t_game *game, unsigned char *process)
{
	int id;
	t_op	*op_tab;

	op_tab = ft_get_op();
	id = ft_reverse_bytes(process, 4);
	game->process->alive += op_tab[0].cycles;
	game->process->duration += op_tab[0].cycles;
	if (id >= 0 && id < 4)
	{
		game->champ[id].alive += 1;
		ft_printf("Player %i (%s) is alive!\n", game->champ[id].nbr, game->champ[id].header.prog_name);
		return (4);
	}
	return (0);
}

void	ft_add_process(t_game *game)
{
	t_process *new;
	t_process *last;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		exit(1); //ft_error
	ft_bzero(new, sizeof(new));
	new->current = game->arena;
	if (!game->process)
		game->process = new;
	else
	{
		last = game->process;
		while (last->next)
			 last = last->next;
		last->next = new;
	}
}

void	ft_game(t_game *game)
{
	int		i;

	i = 0;
	ft_add_process(game);
	game->cycle = 4096;
	while (i < game->cycle)
	{
		if (game->process->current[i] == 1)
			i += op_live(game, &game->process->current[i + 1]);
		i++;
	}
}