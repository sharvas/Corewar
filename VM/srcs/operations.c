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
	unsigned int	index;
	unsigned int	reg;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(1);
	find_args(&process->current[++process->index % MEM_SIZE], args);
	if (args[0] == DIR_CODE && args[1] == REG_CODE
	&& process->current[(process->index + DIR_SIZE) % MEM_SIZE] >= 0
	&& process->current[(process->index + DIR_SIZE) % MEM_SIZE] < 16)
	{
		index = ft_reverse_bytes(&process->current[++process->index % MEM_SIZE], DIR_SIZE);
		process->reg[process->current[(process->index + DIR_SIZE) % MEM_SIZE]] = index;
		process->index += DIR_SIZE;
		process->duration += op_tab.cycles;
		if (op_tab.carry)
			process->carry = 1;
	}
	else if (args[0] == IND_CODE && args[1] == REG_CODE
	&& process->current[(process->index + IND_SIZE) % MEM_SIZE] >= 0
	&& process->current[(process->index + IND_SIZE) % MEM_SIZE] < 16)
	{
		index = ft_reverse_bytes(&process->current[++process->index % MEM_SIZE], IND_SIZE);
		reg = ft_reverse_bytes(&process->current[(((process->index + index - 2) % MEM_SIZE) % IDX_MOD)], DIR_SIZE);
		process->reg[process->current[(process->index + IND_SIZE) % MEM_SIZE]] = reg;
		process->index += IND_SIZE;
		process->duration += op_tab.cycles;
		if (op_tab.carry)
			process->carry = 1;
	}
}

void	op_st(t_process *process)
{
	unsigned char	reg;
	unsigned int	index;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(2);
	find_args(&process->current[++process->index % MEM_SIZE], args);
	if (args[0] == REG_CODE && args[1] == IND_CODE
	&& process->current[(process->index + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + 1) % MEM_SIZE] < 16)
	{
		reg = process->current[++process->index % MEM_SIZE];
		index = ft_reverse_bytes(&process->current[++process->index % MEM_SIZE], IND_SIZE);
		process->current[((process->index + index - 2) % MEM_SIZE) % IDX_MOD] = ft_reverse_bytes(&process->reg[reg], DIR_SIZE);
		process->duration += op_tab.cycles;
		process->index += IND_SIZE - 1;
	}
	else if (args[0] == REG_CODE && args[1] == REG_CODE
	&& process->current[(process->index + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + 1) % MEM_SIZE] < 16
	&& process->current[(process->index + 2) % MEM_SIZE] >= 0
	&& process->current[(process->index + 2) % MEM_SIZE] < 16)
	{
		reg = process->current[++process->index % MEM_SIZE];
		process->reg[process->current[++process->index % MEM_SIZE]] = process->reg[reg];
		process->duration += op_tab.cycles;
	}
}

void	op_add(t_process *process)
{
	unsigned int	reg1;
	unsigned int	reg2;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(3);
	find_args(&process->current[++process->index % MEM_SIZE], args);
	if (args[0] == REG_CODE && args[1] == REG_CODE && args[2] == REG_CODE
	&& process->current[(process->index + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + 1) % MEM_SIZE] < 16
	&& process->current[(process->index + 2) % MEM_SIZE] >= 0
	&& process->current[(process->index + 2) % MEM_SIZE] < 16
	&& process->current[(process->index + 3) % MEM_SIZE] >= 0
	&& process->current[(process->index + 3) % MEM_SIZE] < 16)
	{
		reg1 = process->reg[process->current[++process->index % MEM_SIZE]];
		reg2 = process->reg[process->current[++process->index % MEM_SIZE]];
		process->reg[process->current[++process->index % MEM_SIZE]] = reg1 + reg2;
		process->duration += op_tab.cycles;
		if (reg1 + reg2 == 0 && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;
	}
}

void	op_sub(t_process *process)
{
	unsigned int	reg1;
	unsigned int	reg2;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(4);
	find_args(&process->current[++process->index % MEM_SIZE], args);
	if (args[0] == REG_CODE && args[1] == REG_CODE && args[2] == REG_CODE
	&& process->current[(process->index + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + 1) % MEM_SIZE] < 16
	&& process->current[(process->index + 2) % MEM_SIZE] >= 0
	&& process->current[(process->index + 2) % MEM_SIZE] < 16
	&& process->current[(process->index + 3) % MEM_SIZE] >= 0
	&& process->current[(process->index + 3) % MEM_SIZE] < 16)
	{
		reg1 = process->reg[process->current[++process->index % MEM_SIZE]];
		reg2 = process->reg[process->current[++process->index % MEM_SIZE]];
		process->reg[process->current[++process->index % MEM_SIZE]] = reg1 - reg2;
		process->duration += op_tab.cycles;
		if (reg1 - reg2 == 0 && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;
	}
}

void	op_and(t_process *process)
{
	t_op		op_tab;
	t_arg_type	args[4];

	op_tab = ft_get_op(5);
	find_args(&process->current[++process->index % MEM_SIZE], args);

}