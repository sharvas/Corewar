/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:44:35 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_zjmp(t_game *game, t_process *process)
{
	t_op	op_tab;
	short	index;
	short	sign;

	op_tab = ft_get_op(8);
	sign = 1;
	index = ft_reverse_bytes(&game->arena[++process->index % MEM_SIZE], IND_SIZE);
	if (index < 0)
	{
		sign = -1;
		index = -index;
	}
	if (process->carry)
		process->index += sign * ((index % IDX_MOD) % MEM_SIZE) - 2;
	process->duration += op_tab.cycles;
}

void	op_aff(t_process *process)
{
	t_op			op_tab;

	op_tab = ft_get_op(15);
	process->duration += op_tab.cycles;//
}