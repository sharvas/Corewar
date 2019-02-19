/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and_or.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:52:36 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/13 11:52:37 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_and(t_game *game, t_process *process)
{
	int				val[2];
	unsigned int	size[2];
	t_arg_type		args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args, game->flag_arg);
	get_size(&size[0], args[0], 1);
	get_size(&size[1], args[1], 1);
	if (args[0] && args[1] && args[2] == REG_CODE
	&& check_args(game, process->seek, args, 6))
	{
		get_first_value(game, process, args, &val[0]);
		get_second_value(game, process, args, &val[1]);
		process->reg[game->arena[++process->seek % MEM_SIZE]] = val[0] & val[1];
		if (game->flag_op)
			ft_printf("AND(%i) value1: %i, value2: %i, reg: %i\n",
		process->champ, val[0], val[1], game->arena[process->seek % MEM_SIZE]);
		if ((val[0] & val[1]) == 0)
			process->carry = 1;
		else
			process->carry = 0;
		process->index = process->seek;
	}
	else
		process->index = move_index(process->index, args, 6);
}

void	op_or(t_game *game, t_process *process)
{
	int				val[2];
	unsigned int	size[2];
	t_arg_type		args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args, game->flag_arg);
	get_size(&size[0], args[0], 1);
	get_size(&size[1], args[1], 1);
	if (args[0] && args[1] && args[2] == REG_CODE
	&& check_args(game, process->seek, args, 7))
	{
		get_first_value(game, process, args, &val[0]);
		get_second_value(game, process, args, &val[1]);
		process->reg[game->arena[++process->seek % MEM_SIZE]] = val[0] | val[1];
		if (game->flag_op)
			ft_printf("OR(%i) value1: %i, value2: %i, reg: %i\n",
		process->champ, val[0], val[1], game->arena[process->seek % MEM_SIZE]);
		if ((val[0] | val[1]) == 0)
			process->carry = 1;
		else
			process->carry = 0;
		process->index = process->seek;
	}
	else
		process->index = move_index(process->index, args, 7);
}

void	op_xor(t_game *game, t_process *process)
{
	int				val[2];
	unsigned int	size[2];
	t_arg_type		args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args, game->flag_arg);
	get_size(&size[0], args[0], 1);
	get_size(&size[1], args[1], 1);
	if (args[0] && args[1] && args[2] == REG_CODE
	&& check_args(game, process->seek, args, 8))
	{
		get_first_value(game, process, args, &val[0]);
		get_second_value(game, process, args, &val[1]);
		process->reg[game->arena[++process->seek % MEM_SIZE]] = val[0] ^ val[1];
		if (game->flag_op)
			ft_printf("XOR(%i) value1: %i, value2: %i, reg: %i\n",
		process->champ, val[0], val[1], game->arena[process->seek % MEM_SIZE]);
		if ((val[0] ^ val[1]) == 0)
			process->carry = 1;
		else
			process->carry = 0;
		process->index = process->seek;
	}
	else
		process->index = move_index(process->index, args, 8);
}
