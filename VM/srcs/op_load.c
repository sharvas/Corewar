/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:48:24 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/13 11:48:24 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_ld(t_game *game, t_process *process)
{
	int			value;
	short		index;
	t_op		op_tab;
	t_arg_type	args[4];

	op_tab = ft_get_op(1);
	find_args(&game->arena[++process->index % MEM_SIZE], args);
	if (args[0] == DIR_CODE && args[1] == REG_CODE
	&& game->arena[(process->index + DIR_SIZE + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + DIR_SIZE + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		value = ft_reverse_bytes(&game->arena[++process->index % MEM_SIZE], DIR_SIZE);
		process->reg[*(game->arena + ((process->index + DIR_SIZE) % MEM_SIZE))] = value;

		// ft_printf("champ(%u): load (T_DIR %u, T_REG %u)\n", process->champ, value,
		// 	game->arena[(process->index + DIR_SIZE) % MEM_SIZE]);
		
		process->index += DIR_SIZE;
		process->duration += op_tab.cycles;
		if (op_tab.carry)
			process->carry = 1;
	}
	else if (args[0] == IND_CODE && args[1] == REG_CODE
	&& game->arena[(process->index + IND_SIZE + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + IND_SIZE + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		ft_get_index(&game->arena[++process->index % MEM_SIZE], IND_SIZE, &index);
		value = ft_reverse_bytes(&game->arena[(process->index - 2 + index) % MEM_SIZE], DIR_SIZE);

		// ft_printf("champ(%u): load (T_IND %% IDX_MOD %u, T_REG %u)\n", process->champ, value,
		// 	game->arena[(process->index + IND_SIZE) % MEM_SIZE]);
		
		process->reg[game->arena[(process->index + IND_SIZE) % MEM_SIZE]] = value;
		process->index += IND_SIZE;
		process->duration += op_tab.cycles;
		if (op_tab.carry)
			process->carry = 1;
	}
}

void	op_ldi(t_game *game, t_process *process)
{
	unsigned int	size1;
	unsigned int	size2;
	short			value1;
	short			value2;
	short			total_index;
	int				total_value;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(9);
	find_args(&game->arena[++process->index % MEM_SIZE], args);
	ft_get_size(&size1, args[0], 1);
	ft_get_size(&size2, args[1], 1);
	if (args[0] && (args[1] == DIR_CODE || args[1] == REG_CODE) && args[2] == REG_CODE
	&& game->arena[(process->index + size1 + size2 + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + size1 + size2 + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		// reverse incrementation if second does not succeed or do not increment the first?? everywhere
		if (!get_first_value_ind(game, process, args[0], &value1))
			return ;
		if (!get_second_value_ind(game, process, args[1], &value2))
			return ;
		ft_index_sum(value1, value2, &total_index);
		total_value = ft_reverse_bytes(&game->arena[(process->index - size1
			- size2 - 1 + total_index) % MEM_SIZE], REG_SIZE);
		process->reg[game->arena[(process->index + 1) % MEM_SIZE]] = total_value;
		process->duration += op_tab.cycles;
		if (total_value == 0 && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;
	}
}

void	op_lld(t_game *game, t_process *process)
{
	int			value;
	short		index;
	t_op		op_tab;
	t_arg_type	args[4];

	op_tab = ft_get_op(12);
	find_args(&game->arena[++process->index % MEM_SIZE], args);
	if (args[0] == DIR_CODE && args[1] == REG_CODE
	&& game->arena[(process->index + DIR_SIZE + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + DIR_SIZE + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		value = ft_reverse_bytes(&game->arena[++process->index % MEM_SIZE], DIR_SIZE);
		process->reg[*(game->arena + ((process->index + DIR_SIZE) % MEM_SIZE))] = value;

		// ft_printf("champ(%u): load (T_DIR %u, T_REG %u)\n", process->champ, value,
		// 	game->arena[(process->index + DIR_SIZE) % MEM_SIZE]);
		
		process->index += DIR_SIZE;
		process->duration += op_tab.cycles;
		if (op_tab.carry)
			process->carry = 1;
	}
	else if (args[0] == IND_CODE && args[1] == REG_CODE
	&& game->arena[(process->index + IND_SIZE + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + IND_SIZE + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		index = ft_reverse_bytes(&game->arena[++process->index % MEM_SIZE], IND_SIZE);
		value = ft_reverse_bytes(&game->arena[(process->index - 2 + index) % MEM_SIZE], DIR_SIZE);

		// ft_printf("champ(%u): load (T_IND %% IDX_MOD %u, T_REG %u)\n", process->champ, value,
		// 	game->arena[(process->index + IND_SIZE) % MEM_SIZE]);
		
		process->reg[game->arena[(process->index + IND_SIZE) % MEM_SIZE]] = value;
		process->index += IND_SIZE;
		process->duration += op_tab.cycles;
		if (op_tab.carry)
			process->carry = 1;
	}
}

void	op_lldi(t_game *game, t_process *process)
{
	unsigned int	size1;
	unsigned int	size2;
	short			value1;
	short			value2;
	short			total_index;
	int				total_value;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(9);
	find_args(&game->arena[++process->index % MEM_SIZE], args);
	ft_get_size(&size1, args[0], 1);
	ft_get_size(&size2, args[1], 1);
	if (args[0] && (args[1] == DIR_CODE || args[1] == REG_CODE) && args[2] == REG_CODE
	&& game->arena[(process->index + size1 + size2 + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + size1 + size2 + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		// reverse incrementation if second does not succeed or do not increment the first?? everywhere
		if (!get_first_value_ind(game, process, args[0], &value1))
			return ;
		if (!get_second_value_ind(game, process, args[1], &value2))
			return ;
		total_index = value1 + value2;
		total_value = ft_reverse_bytes(&game->arena[(process->index - size1
			- size2 - 1 + total_index) % MEM_SIZE], REG_SIZE);
		process->reg[game->arena[(process->index + 1) % MEM_SIZE]] = total_value;
		process->duration += op_tab.cycles;
		if (total_value == 0 && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;
	}
}