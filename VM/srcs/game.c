#include "vm.h"

int		ft_reverse_bytes(void *ptr, int size)
{
	short		ret_two;
	int			ret_four;
	int			i;

	ret_two = 0;
	ret_four = 0;
	i = 0;
	if (size == 2)
	{
		while (size-- > 0)
		{
			ret_two |= *((unsigned char *)ptr + i) << (size * 8);
			i++;
		}
		return (ret_two);
	}
	else if (size == 4)
	{
		while (size-- > 0)
		{
			ret_four |= *((unsigned char *)ptr + i) << (size * 8);
			i++;
		}
		return (ret_four);
	}
	return (0);
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
	id = ft_reverse_bytes(&game->arena[(process->index + 1) % MEM_SIZE], DIR_SIZE);
	process->alive = 1;
	process->duration += op_tab.cycles;
	if (id > 0 && id <= game->champ_count)
	{
		game->alive++;
		game->champ[id].alive++;
		ft_printf("Player %i (%s) is alive!\n", game->champ[id].nbr, game->champ[id].header.prog_name);
	}
	process->index += DIR_SIZE;
}

// void	ft_fork_process(t_game *game, t_process *parent)
// {
// 	t_process *new;
// 	t_process *last;
// 	int			i;

// 	i = 0;
// 	if (!(new = (t_process *)malloc(sizeof(t_process))))
// 		exit(1); //ft_error
// 	ft_bzero(new, sizeof(*new));
// 	new->current = game->arena;//?
// 	new->index = game->champ[champ].start_index;// + (index % IDX_MOD) % MEM_SIZE
// 	new->champ = parent->champ;
// 	new->alive = parent->alive;
// 	while (++i <= 16)
// 		new->reg[i] = parent->reg[i];
// 	last = game->process;//add to end like this?
// 	while (last->next)//add to end like this?
// 		last = last->next;//add to end like this?
// 	last->next = new;//add to end like this?
// }

void	ft_add_process(t_game *game, int champ)
{
	t_process *new;
	t_process *last;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		exit(1); //ft_error
	ft_bzero(new, sizeof(*new));
	new->index = game->champ[champ].start_index;
	new->champ = champ;
	new->reg[1] = champ;
	new->alive = 0;
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
	int				i;
	t_process		*process;

	i = 1;
	while (i <= game->champ_count)
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
				if (game->arena[process->index % MEM_SIZE] == 1)
					op_live(game, process);
				else if (game->arena[process->index % MEM_SIZE] == 2)
					op_ld(game, process);
				else if (game->arena[process->index % MEM_SIZE] == 3)
					op_st(game, process);
				else if (game->arena[process->index % MEM_SIZE] == 4)
					op_add(game, process);
				else if (game->arena[process->index % MEM_SIZE] == 5)
					op_sub(game, process);
				else if (game->arena[process->index % MEM_SIZE] == 6)
					op_and(game, process);
				else if (game->arena[process->index % MEM_SIZE] == 7)
					op_or(game, process);
				else if (game->arena[process->index % MEM_SIZE] == 8)
					op_xor(game, process);
				else if (game->arena[process->index % MEM_SIZE] == 9)
					op_zjmp(game, process);
				else if (game->arena[process->index % MEM_SIZE] == 10)
					op_ldi(game, process);
				else if (game->arena[process->index % MEM_SIZE] == 11)
					op_sti(game, process);
				// else if (process->current[process->index % MEM_SIZE] == 12)
				// 	op_fork(process, game);
				else if (game->arena[process->index % MEM_SIZE] == 13)
					op_lld(process);
				else if (game->arena[process->index % MEM_SIZE] == 14)
					op_lldi(process);
				else if (game->arena[process->index % MEM_SIZE] == 15)
					op_lfork(process);
				else if (game->arena[process->index % MEM_SIZE] == 16)
					op_aff(process);
				process->index = process->index % MEM_SIZE + 1;
				process = process->next;
			}
			ft_printf("\033[H\033[?25l");
			print_arena_color(game);
			ft_printf("\n\033[?12;25h");
			usleep(100000);
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