/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:48:31 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/13 11:48:32 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	spread_color(int index, t_game *game, t_process *process)
{
	int	i;

	i = 0;
	while (i < 4)
		ft_memcpy(game->arena_champs + index + i++, &process->champ, 1);
}

void	    op_st(t_game *game, t_process *process)
{
	short			index;
	unsigned char	reg_index;
	int				sign;
	t_op			op_tab;
	t_arg_type		args[4];

	sign = 1;
	op_tab = ft_get_op(2);
	find_args(&game->arena[++process->index % MEM_SIZE], args);
	if (args[0] == REG_CODE && args[1] == IND_CODE
	&& game->arena[(process->index + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		reg_index = game->arena[++process->index % MEM_SIZE];
		index = ft_reverse_bytes(&game->arena[++process->index % MEM_SIZE], IND_SIZE);
		if (index < 0)
		{
			index = -index;
			sign = -1;
		}
		index = index % IDX_MOD;
		
		ft_printf("champ(%u): store (T_REG %u, T_IND %i)\n", process->champ, reg_index, index * sign);
		
		*(int *)(game->arena + (process->index + index - 2) % MEM_SIZE) = ft_reverse_bytes(&process->reg[reg_index], DIR_SIZE);
		process->duration += op_tab.cycles;
		spread_color((process->index + index - 2) % MEM_SIZE, game, process);/////////
		process->index += IND_SIZE - 1;
	}
	else if (args[0] == REG_CODE && args[1] == REG_CODE
	&& game->arena[(process->index + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + 1) % MEM_SIZE] <= REG_NUMBER
	&& game->arena[(process->index + 2) % MEM_SIZE] >= 1
	&& game->arena[(process->index + 2) % MEM_SIZE] <= REG_NUMBER)
	{
		reg_index = game->arena[++process->index % MEM_SIZE];

		ft_printf("champ(%u): store (T_REG %u, T_REG %u)\n", process->champ, reg_index,
			game->arena[(process->index + 1) % MEM_SIZE]);
		
		process->reg[game->arena[++process->index % MEM_SIZE]] = process->reg[reg_index];
		process->duration += op_tab.cycles;
	}
}

void	    op_sti(t_game *game, t_process *process)
{
	unsigned int	size1;
	unsigned int	size2;
	short			value1;
	short			value2;
	short			total_index;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(10);
	find_args(game->arena + (++process->index % MEM_SIZE), args);
	ft_get_size(&size1, args[1], 2);
	ft_get_size(&size2, args[2], 2);
	if (args[0] == REG_CODE &&  args[1] && (args[2] == DIR_CODE || args[2] == REG_CODE)
	&& *(game->arena + (process->index + 1) % MEM_SIZE) >= 1
	&& *(game->arena + (process->index + 1) % MEM_SIZE) <= REG_NUMBER)
	{
		// reverse incrementation if second does not succeed or do not increment the first?? everywhere
		process->index++;
		if (!get_first_value_ind(game, process, args[1], &value1))
			return ;
		if (!get_second_value_ind(game, process, args[2], &value2))
			return ;
		total_index = (value1 + value2) % IDX_MOD;
		*(int *)(game->arena + ((process->index - size1 - size2 - 2 + total_index) % MEM_SIZE))
		= ft_reverse_bytes(&process->reg[*(game->arena + (process->index - size1 - size2) % MEM_SIZE)], REG_SIZE);
		
		ft_printf("champ (%u): store index (T_REG %u -> %u) // index - %i value1 - %u value2 - %u rev - %u\n",
		process->champ, *(game->arena + (process->index - size1 - size2) % MEM_SIZE), total_index,
		process->index, value1, value2, *(int *)(process->reg + *(game->arena + (process->index - size1 - size2)
			% MEM_SIZE)));
		
		process->duration += op_tab.cycles;
		spread_color(((process->index - size1 - size2 - 2 + total_index) % MEM_SIZE), game, process);
		if (!total_index && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;
	}
}