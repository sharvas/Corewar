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

void		reset_live(t_game *game)
{
	int	i;

	i = 0;
	while (++i <= game->champ_count)
		game->champ[i].alive_count = 0;
	game->alive_count = 0;
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

int		who_won(t_game *game)
{
	int	champ;
	int	i;

	i = game->champ_count;
	champ = game->champ_count;
	while (i > 0)
	{
		if (game->champ[i].last_alive >= game->champ[champ].last_alive)
			champ = i;
		i--;
	}
	return (champ);
}

void	print_winner(t_game *game)
{
	short	winner;

	winner = who_won(game);
	if (!game->dump_set)
	{
		if (!game->champ[winner].last_alive)
			ft_printf("No player won, no player lived\n");
		else
			ft_printf("Player %d (%s) won\n", game->champ[winner].nbr, game->champ[winner].header.prog_name);
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
	while (game->cycle_to_die > 0 && game->process)
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
					process->index = (process->index + 1) % MEM_SIZE;
					process->duration_set = ft_add_duration(game, process);
				}
				else if (process->duration)
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
					process->index = (process->index + 1) % MEM_SIZE;
					process->duration_set = ft_add_duration(game, process);
				}
				process = process->next;
			}
			if (game->flag_v && game->cycle_count >= game->flag_w)
				print_visualizer(game, i);
			if (game->cycle_count && game->cycle_count == game->flag_dump)
			{
				if (game->flag_v)
					exit(1);//free everything first?
				print_dump(game->arena);
			}
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
	print_winner(game);
	// if (!game->dump_set)
	// 	ft_printf("Player %d (%s) won\n", game->champ[who_won(game)].nbr, game->champ[who_won(game)].header.prog_name);//find champion declared alive last
}
