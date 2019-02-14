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
			if (game->cycle % game->frame_rate == 0)
				ft_printf("\033[2J");
			ft_printf("\033[H\033[?25l");
			print_arena_color(game);
			ft_printf("\nCycle to die: %.4i, Cycle %.4i, Checks %.2i\n", game->cycle_to_die, game->cycle, i);
			ft_printf("Process count: %.2i\n", ft_count_process(game));
			ft_printf("\n\033[?12;25h");
			usleep(1000);
			game->cycle--;
		}
		if (i >= MAX_CHECKS || game->alive_count >= NBR_LIVE)
		{
			game->cycle_to_die -= CYCLE_DELTA;
			i = 1;
		}
		ft_check_process(game);
	}
}
