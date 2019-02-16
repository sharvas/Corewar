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
	int				ret[2];
	int				value1;
	int				value2;
	unsigned int	size1;
	unsigned int	size2;
	t_arg_type		args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args);
	ft_get_size(&size1, args[0], 1);
	ft_get_size(&size2, args[1], 1);
	if (args[0] && args[1] && args[2] == REG_CODE
	&& game->arena[(process->seek + size1 + size2 + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->seek + size1 + size2 + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		ret[0] = get_first_value(game, process, args, &value1);
		ret[1] = get_second_value(game, process, args, &value2);
		if (ret[0] && ret[1])
		{
			process->reg[game->arena[++process->seek % MEM_SIZE]] = value1 & value2;
			// ft_printf("AND(%i) value1: %i, value2: %i, sum: %i\n", process->champ, value1, value2, value1 & value2);
			if ((value1 & value2) == 0)
				process->carry = 1;
			else
				process->carry = 0;
			process->index = process->seek;
		}
	}
	else
		process->index = ft_move_index(process->index, args, 6);
}

void	op_or(t_game *game, t_process *process)
{
	int				ret[2];
	int				value1;
	int				value2;
	unsigned int	size1;
	unsigned int	size2;
	t_arg_type		args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args);
	ft_get_size(&size1, args[0], 1);
	ft_get_size(&size2, args[1], 1);
	if (args[0] && args[1] && args[2] == REG_CODE
	&& game->arena[(process->seek + size1 + size2 + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->seek + size1 + size2 + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		ret[0] = get_first_value(game, process, args, &value1);
		ret[1] = get_second_value(game, process, args, &value2);
		if (ret[0] && ret[1])
		{
			process->reg[game->arena[++process->seek % MEM_SIZE]] = value1 | value2;
			// ft_printf("OR(%i) value1: %i, value2: %i, sum: %i\n", process->champ, value1, value2, value1 | value2);
			if ((value1 | value2) == 0)
				process->carry = 1;
			else
				process->carry = 0;
			process->index = process->seek;
		}
	}
	else
		process->index = ft_move_index(process->index, args, 7);
}

void	op_xor(t_game *game, t_process *process)
{
	int				ret[2];
	int				value1;
	int				value2;
	unsigned int	size1;
	unsigned int	size2;
	t_arg_type		args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args);
	ft_get_size(&size1, args[0], 1);
	ft_get_size(&size2, args[1], 1);
	if (args[0] && args[1] && args[2] == REG_CODE
	&& game->arena[(process->seek + size1 + size2 + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->seek + size1 + size2 + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		ret[0] = get_first_value(game, process, args, &value1);
		ret[1] = get_second_value(game, process, args, &value2);
		if (ret[0] && ret[1])
		{
			process->reg[game->arena[++process->seek % MEM_SIZE]] = value1 ^ value2;
			// ft_printf("XOR(%i) value1: %i, value2: %i, sum: %i\n", process->champ, value1, value2, value1 ^ value2);
			if ((value1 ^ value2) == 0)
				process->carry = 1;
			else
				process->carry = 0;
			process->index = process->seek;
		}
	}
	else
		process->index = ft_move_index(process->index, args, 8);
}