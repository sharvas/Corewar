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
	int				value1;
	int				value2;
	unsigned int	size1;
	unsigned int	size2;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(5);
	process->seek_index = process->index;
	find_args(&game->arena[++process->seek_index % MEM_SIZE], args);
	ft_get_size(&size1, args[0], 1);
	ft_get_size(&size2, args[1], 1);
	if (args[0] && args[1] && args[2] == REG_CODE
	&& game->arena[(process->index + size1 + size2 + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + size1 + size2 + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		if (!get_first_value(game, process, args, &value1))
			return ;
		if (!get_second_value(game, process, args, &value2))
			return ;
		process->reg[game->arena[++process->index % MEM_SIZE]] = value1 & value2;
		process->duration += op_tab.cycles;
		if ((value1 & value2) == 0 && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;
	}
}

void	op_or(t_game *game, t_process *process)
{
	int				value1;
	int				value2;
	unsigned int	size1;
	unsigned int	size2;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(6);
	find_args(&game->arena[++process->index % MEM_SIZE], args);
	ft_get_size(&size1, args[0], 1);
	ft_get_size(&size2, args[1], 1);
	if (args[0] && args[1] && args[2] == REG_CODE
	&& game->arena[(process->index + size1 + size2 + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + size1 + size2 + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		if (!get_first_value(game, process, args, &value1))
			return ;
		if (!get_second_value(game, process, args, &value2))
			return ;
		process->reg[game->arena[++process->index % MEM_SIZE]] = value1 | value2;
		process->duration += op_tab.cycles;
		if ((value1 | value2) == 0 && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;
	}
}

void	op_xor(t_game *game, t_process *process)
{
	int				value1;
	int				value2;
	unsigned int	size1;
	unsigned int	size2;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(7);
	find_args(&game->arena[++process->index % MEM_SIZE], args);
	ft_get_size(&size1, args[0], 1);
	ft_get_size(&size2, args[1], 1);
	if (args[0] && args[1] && args[2] == REG_CODE
	&& game->arena[(process->index + size1 + size2 + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + size1 + size2 + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		if (!get_first_value(game, process, args, &value1))
			return ;
		if (!get_second_value(game, process, args, &value2))
			return ;
		process->reg[game->arena[++process->index % MEM_SIZE]] = value1 ^ value2;
		process->duration += op_tab.cycles;
		if ((value1 ^ value2) == 0 && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;
	}
}