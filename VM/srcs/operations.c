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

void	find_args(unsigned char *ptr, t_arg_type arg[])
{
	unsigned char	mask;

	mask = 192;
	arg[0] = (mask & *ptr) >> 6;
	arg[1] = ((mask >> 2) & *ptr) >> 4;
	arg[2] = ((mask >> 4) & *ptr) >> 2;
	arg[3] = (mask >> 6) & *ptr;
}

void	op_ld(t_process *process)
{
	int				index;
	t_op			*op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op();
	find_args(&process->current[++process->index % MEM_SIZE], args);
	if (args[0] == DIR_CODE && args[1] == REG_CODE
	&& process->current[(process->index + DIR_SIZE) % MEM_SIZE] >= 0
	&& process->current[(process->index + DIR_SIZE) % MEM_SIZE] < 16)
	{
		index = ft_reverse_bytes(&process->current[(++process->index % MEM_SIZE) % IDX_MOD], DIR_SIZE);
		process->index += DIR_SIZE;
		process->reg[process->current[process->index % MEM_SIZE]] = index;
		process->duration += op_tab[1].cycles;
	}
}

void	op_st(t_process *process)
{
	int				index;
	unsigned char	reg;
	t_op			*op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op();
	find_args(&process->current[++process->index % MEM_SIZE], args);
	if (args[1] == IND_CODE && args[0] == REG_CODE
	&& process->current[(process->index + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + 1) % MEM_SIZE] < 16)
	{
		reg = process->current[++process->index % MEM_SIZE];
		index = ft_reverse_bytes(&process->current[++process->index % MEM_SIZE], IND_SIZE);
		process->current[((process->index + index - 2) % MEM_SIZE) % IDX_MOD] = process->reg[reg];
		process->duration += op_tab[2].cycles;
		process->index += IND_SIZE - 1;
	}
	else if (args[1] == REG_CODE && args[0] == REG_CODE
	&& process->current[(process->index + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + 1) % MEM_SIZE] < 16
	&& process->current[(process->index + 2) % MEM_SIZE] >= 0
	&& process->current[(process->index + 2) % MEM_SIZE] < 16)
	{
		reg = process->current[++process->index % MEM_SIZE];
		process->reg[process->current[++process->index % MEM_SIZE]] = process->reg[reg];
		process->duration += op_tab[2].cycles;
	}
}