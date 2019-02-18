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

static void	ft_init_op(void (*operations[])(t_game *, t_process *))
{
	operations[1] = &op_live;
	operations[2] = &op_ld;
	operations[3] = &op_st;
	operations[4] = &op_add;
	operations[5] = &op_sub;
	operations[6] = &op_and;
	operations[7] = &op_or;
	operations[8] = &op_xor;
	operations[9] = &op_zjmp;
	operations[10] = &op_ldi;
	operations[11] = &op_sti;
	operations[12] = &op_fork;
	operations[13] = &op_lld;
	operations[14] = &op_lldi;
	operations[15] = &op_lfork;
	operations[16] = &op_aff;
}

static void	do_process(t_game *game,
void (*operations[17])(t_game *, t_process *))
{
	t_process	*process;

	process = game->process;
	while (process)
	{
		if (!process->duration_set)
		{
			process->index = (process->index + 1) % MEM_SIZE;
			process->duration_set = add_duration(game, process);
		}
		else if (process->duration)
			process->duration--;
		else if (process->duration_set)
		{
			if (game->arena[process->index % MEM_SIZE] >= 1
			&& game->arena[process->index % MEM_SIZE] <= 16)
				(*operations[game->arena[process->index % MEM_SIZE]])(game,
				process);
			process->index = (process->index + 1) % MEM_SIZE;
			process->duration_set = add_duration(game, process);
		}
		process = process->next;
	}
}

static void	do_cycle(t_game *game,
void (*operations[17])(t_game *, t_process *), int i)
{
	do_process(game, operations);
	if (game->flag_v && game->cycle_count >= game->flag_w)
		print_visualizer(game, i);
	if (game->cycle_count && game->cycle_count == game->flag_dump)
	{
		if (game->flag_v)
		{
			ft_free_game(game);
			exit(1);
		}
		print_dump(game->arena, game);
	}
	game->cycle--;
	game->cycle_count++;
}

static void	print_zero_cycle_flags(t_game *game)
{
	if (game->flag_i)
		print_intro(game);
	if (game->flag_v)
	{
		ft_printf("%s%s", CLEAR, MOVE_CURSOR);
		if (game->dump_set && !game->flag_dump && !game->flag_w)
		{
			print_visualizer(game, 0);
			ft_free_game(game);
			exit(1);
		}
	}
	if (game->dump_set && !game->flag_dump)
	{
		if (game->flag_v && game->flag_w)
			error_exit("-w > 0 but -dump 0", game);
		print_dump(game->arena, game);
	}
}

void		run_game(t_game *game)
{
	int			i;
	void		(*operations[17])(t_game *, t_process *);

	ft_init_op(operations);
	i = 1;
	while (i <= game->champ_total)
		add_process(game, i++);
	i = 0;
	print_zero_cycle_flags(game);
	while (game->cycle_to_die > 0 && game->process)
	{
		i++;
		game->cycle = game->cycle_to_die;
		while (game->cycle > 0)
			do_cycle(game, operations, i);
		if (i >= MAX_CHECKS || game->alive_count >= NBR_LIVE)
		{
			game->cycle_to_die -= CYCLE_DELTA;
			i = 1;
		}
		check_process(game);
		reset_live(game);
	}
	print_winner(game);
}
