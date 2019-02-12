#include "vm.h"

unsigned int	ft_reverse_bytes(void *ptr, int size)
{
	unsigned int	ret;
	int				i;

	ret = 0;
	i = 0;
	while (size-- > 0)
	{
		ret |= *((unsigned char *)ptr + i) << (size * 8);
		i++;
	}
	return (ret);
}

unsigned int	ft_get_bytes(void *ptr, int size)
{
	unsigned int	ret;
	int				i;

	ret = 0;
	i = 0;
	while (size-- > 0)
	{
		ret |= *((unsigned char *)ptr + i) >> (i * 8);
		i++;
	}
	return (ret);
}

void	op_live(t_game *game, t_process *process)
{
	int		id;
	t_op	op_tab;

	op_tab = ft_get_op(0);
	id = ft_reverse_bytes(&process->current[(process->index + 1) % MEM_SIZE], DIR_SIZE);
	process->alive = 1;
	process->duration += op_tab.cycles;
	if (id >= 0 && id < game->champ_count)
	{
		game->alive++;
		game->champ[id].alive++;
		ft_printf("Player %i (%s) is alive!\n", game->champ[id].nbr, game->champ[id].header.prog_name);
	}
	process->index += DIR_SIZE;
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
	new->reg[1] = game->champ[champ].nbr;
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
		ft_add_process(game, i++);
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
				else if (process->current[process->index % MEM_SIZE] == 2)
					op_ld(process);
				else if (process->current[process->index % MEM_SIZE] == 3)
					op_st(process);
				else if (process->current[process->index % MEM_SIZE] == 4)
					op_add(process);
				else if (process->current[process->index % MEM_SIZE] == 5)
					op_sub(process);
				else if (process->current[process->index % MEM_SIZE] == 6)
					op_and(process);
				else if (process->current[process->index % MEM_SIZE] == 7)
					op_or(process);
				else if (process->current[process->index % MEM_SIZE] == 8)
					op_xor(process);
				else if (process->current[process->index % MEM_SIZE] == 9)
					op_zjmp(process);
				else if (process->current[process->index % MEM_SIZE] == 10)
					op_ldi(process);
				else if (process->current[process->index % MEM_SIZE] == 11)
					op_sti(process);
				process->index = process->index % MEM_SIZE + 1;
				process = process->next;
			}
			ft_printf("\033[H\033[?25l");
			print_arena_color(game);
			ft_printf("\n\033[?12;25h");
			usleep(500000);
			if (game->cycle % game->frame_rate == 0)
				ft_printf("\033[2J");
			game->cycle--;
		}
		if (i > MAX_CHECKS || game->alive >= NBR_LIVE)
		{
			game->cycle_to_die -= CYCLE_TO_DIE;
			i = 1;
		}
	}
}