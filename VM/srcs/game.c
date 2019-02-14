/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 09:10:30 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/14 09:10:32 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_reverse_bytes(void *ptr, unsigned int size)
{
	short		ret_two;
	int			ret_four;
	int			i;

	ret_two = 0;
	ret_four = 0;
	i = 0;
	if (size <= 2)
	{
		while (size-- > 0)
		{
			ret_two |= *((unsigned char *)ptr + i) << (size * 8);
			i++;
		}
		return (ret_two);
	}
	else if (size <= 4)
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

void		reset_live(t_game *game)
{
	int	i;

	i = 0;
	while (++i <= game->champ_count)
		game->champ[i].alive_count = 0;
	game->alive_count = 0;
}

t_process	*ft_fork_process(t_game *game, t_process *parent)
{
	t_process	*new;
	t_process	*last;
	int			i;

	i = 0;
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		exit(1); //ft_error
	ft_bzero(new, sizeof(*new));
	new->index = parent->index;
	new->champ = parent->champ;
	new->alive = parent->alive;
	while (++i <= REG_NUMBER)
		new->reg[i] = parent->reg[i];
	last = game->process;
	while (last->next)
		last = last->next;
	last->next = new;
	return (last->next);
}

void	print_visualizer(t_game *game, int i)
{
	short	champ_nbr;
	
	champ_nbr = 0;
	ft_printf("\033[H\033[?25l");
	print_arena_color(game);
	ft_printf("\n\tCycle delta: %2i\t\tNbr_live: %2i/%i \tChecks %.1i/%i\tCycle to die: %-4i\tCycles left in current period: %-4i\tCycle count: %i\n\n", CYCLE_DELTA, game->alive_count, NBR_LIVE, i, MAX_CHECKS, game->cycle_to_die, game->cycle, game->cycle_count);
	ft_printf("\tProcess count: %-21i\n\n", ft_count_process(game));
	ft_printf("\t%sPlayer %i (%s)\tlives in current period: %s%-21d%s \tlast alive: %s%-21d\n", RED, game->champ[1].nbr, game->champ[1].header.prog_name, RESET, game->champ[1].alive_count, RED, RESET, game->champ[1].last_alive);
	if (game->champ_count >= 2)
		ft_printf("\t%sPlayer %i (%s)\tlives in current period: %s%-21d%s \tlast alive: %s%-21d\n", GREEN, game->champ[2].nbr, game->champ[2].header.prog_name, RESET, game->champ[2].alive_count, GREEN, RESET, game->champ[2].last_alive);
	if (game->champ_count >= 3)
		ft_printf("\t%sPlayer %i (%s)\tlives in current period: %s%-21d%s \tlast alive: %s%-21d\n", BLUE, game->champ[3].nbr, game->champ[3].header.prog_name, RESET, game->champ[3].alive_count, BLUE, RESET, game->champ[3].last_alive);
	if (game->champ_count >= 4)
		ft_printf("\t%sPlayer %i (%s)\tlives in current period: %s%-21d%s \tlast alive: %s%-21d", YELLOW, game->champ[4].nbr, game->champ[4].header.prog_name, RESET, game->champ[4].alive_count, YELLOW, RESET, game->champ[4].last_alive);
	ft_printf("\n\033[?12;25h");
	// usleep(400000);
}

int		ft_add_duration(t_game *game, t_process *process)
{
	t_op			op_tab;
	unsigned char	index;

	index = game->arena[process->index];
	if (index > 0 && index < 17)
	{
		op_tab = ft_get_op(index - 1);
		process->duration = op_tab.cycles;
		return (op_tab.cycles);
	}
	return (0);
}

void	ft_game(t_game *game)
{
	int				i;
	int				duration;
	t_process		*process;

	i = 1;
	while (i <= game->champ_count)
		ft_add_process(game, i++);
	i = 0;
	while (game->cycle_to_die > 0 || !game->process)
	{
		i++;
		game->cycle = game->cycle_to_die;
		while (game->cycle > 0)
		{
			// usleep(500000);
			// ft_printf("\033[2J");
			process = game->process;
			while (process)
			{
				if (!process->duration_set)
				{
					process->index = (process->index % MEM_SIZE) + 1;
					process->duration_set = ft_add_duration(game, process);
				}
				if (process->duration)
					process->duration--;
				else if (process->duration_set)
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
					else if (game->arena[process->index % MEM_SIZE] == 12)
						op_fork(game, process);
					else if (game->arena[process->index % MEM_SIZE] == 13)
						op_lld(game, process);
					else if (game->arena[process->index % MEM_SIZE] == 14)
						op_lldi(game, process);
					else if (game->arena[process->index % MEM_SIZE] == 15)
						op_lfork(game, process);
					else if (game->arena[process->index % MEM_SIZE] == 16)
						op_aff(game, process);
					process->index = process->index % MEM_SIZE + 1;
					process->duration_set = ft_add_duration(game, process);
				}
				process = process->next;
			}
			if (game->flag_v)
				print_visualizer(game, i);
			game->cycle--;
			game->cycle_count++;
		}
		if (i >= MAX_CHECKS || game->alive_count >= NBR_LIVE)
		{
			game->cycle_to_die -= CYCLE_DELTA;
			i = 1;
		}
		ft_check_process(game);
		reset_live(game);
	}
	// who_wins(game);
	ft_printf("Player X (champion_name) won");//find champion declared alive last
}
