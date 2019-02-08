#include "vm.h"

long long	ft_reverse_bytes(unsigned char *ptr, int size)
{
	long long	ret;
	int			i;

	ret = 0;
	i = 0;
	while (size-- > 0)
	{
		ret |= *(ptr + i) << (size * 8);
		i++;
	}
	return (ret);
}

void	op_live(t_game *game, t_process *process)
{
	int		id;
	t_op	*op_tab;

	op_tab = ft_get_op();
	id = ft_reverse_bytes(&process->current[(process->index + 1) % MEM_SIZE], sizeof(id));
	process->alive++;
	process->duration += op_tab[0].cycles;
	if (id >= 0 && id <= game->champ_count)
	{
		game->alive += 1;
		ft_printf("Player %i (%s) is alive!\n", game->champ[id].nbr, game->champ[id].header.prog_name);
		process->index += 4;
	}
}

void	ft_add_process(t_game *game, int champ)
{
	t_process *new;
	t_process *last;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		exit(1); //ft_error
	ft_bzero(new, sizeof(*new));
	new->current = game->arena;
	new->index = game->champ[champ].start_index;
	new->champ = champ;
	new->alive = 1;
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
	int			i;
	t_process	*process;

	i = 0;
	while (i < 4 && game->champ[i].header.magic)
	{
		ft_add_process(game, i);
		i++;
	}
	i = 0;
	while (game->cycle_to_die > 0)
	{
		i++;
		game->cycle = game->cycle_to_die;
		while (game->cycle > 0)
		{
			process = game->process;
			while (process)
			{
				if (process->current[process->index % MEM_SIZE] == 1)
					op_live(game, process);
				if (process->index > MEM_SIZE)
					process->index -= MEM_SIZE;
				process->index++;
				process = process->next;
			}
			if (game->cycle % game->frame_rate == 0)
			{
				ft_printf("\033[H\033[2J\n");
				print_arena_color(game);
				usleep(250000);
			}
			game->cycle--;
		}
		if (i > MAX_CHECKS || game->alive >= NBR_LIVE)
		{
			game->cycle_to_die -= CYCLE_TO_DIE;
			i = 1;
		}
	}
}