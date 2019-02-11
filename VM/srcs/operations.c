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
	&& process->current[(process->index + DIR_SIZE + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + DIR_SIZE + 1) % MEM_SIZE] < 16)
	{
		index = ft_reverse_bytes(&process->current[++process->index % MEM_SIZE], DIR_SIZE);
		ft_printf("champ(%u) - load(%u, %u)\n", process->champ, index, process->current[(process->index + DIR_SIZE) % MEM_SIZE]);
		process->reg[process->current[(process->index + DIR_SIZE) % MEM_SIZE]] = index;
		process->index += DIR_SIZE;
		process->duration += op_tab.cycles;
		if (op_tab.carry)
			process->carry = 1;
	}
	else if (args[0] == IND_CODE && args[1] == REG_CODE
	&& process->current[(process->index + IND_SIZE + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + IND_SIZE + 1) % MEM_SIZE] < 16)
	{
		index = ft_reverse_bytes(&process->current[++process->index % MEM_SIZE], IND_SIZE);
		reg = ft_reverse_bytes(&process->current[(((process->index + index - 2) % MEM_SIZE) % IDX_MOD)], DIR_SIZE);
		ft_printf("champ(%u) - load(%u, %u)\n", process->champ, reg, process->current[(process->index + IND_SIZE) % MEM_SIZE]);
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

int		get_first_value(t_process *process, t_arg_type *args, unsigned int *value1)
{
	unsigned int index;

	if (args[0] == REG_CODE
	&& process->current[(process->index + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + 1) % MEM_SIZE] < 16)
	{
		// don't need to reverse, just take 2 bytes
		*value1 = ft_reverse_bytes(&process->reg[process->current[++process->index % MEM_SIZE]], DIR_SIZE);
		return (1);
	}
	else if (args[0] == DIR_CODE)
	{
		*value1 = ft_reverse_bytes(&process->current[(process->index + 1) % MEM_SIZE], DIR_SIZE);
		process->index += DIR_SIZE;
		return (1);
	}
	else if (args[0] == IND_CODE)
	{
		index = ft_reverse_bytes(&process->current[(process->index + 1) % MEM_SIZE], IND_SIZE);
		*value1 = ft_reverse_bytes(&process->current[(process->index + index - 1) % MEM_SIZE], DIR_SIZE);
		process->index += IND_SIZE;
		return (1);
	}
	else
		return (0);
}

void	ft_get_size(unsigned int *size, t_arg_type args)
{
	if (args == REG_CODE)
		*size = T_REG;
	else if (args == IND_CODE)
		*size = IND_SIZE;
	else if (args == DIR_CODE)
		*size = DIR_SIZE;
	else
		*size = 0;
}

int		get_second_value(t_process *process, t_arg_type *args, unsigned int *value2)
{
	unsigned int	index;
	unsigned int	size;

	ft_get_size(&size, args[0]);
	if (args[1] == REG_CODE
	&& process->current[(process->index + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + 1) % MEM_SIZE] < 16)
	{
		// don't need to reverse, just take 2 bytes
		*value2 = ft_reverse_bytes(&process->reg[process->current[++process->index % MEM_SIZE]], DIR_SIZE);
		return (1);
	}
	else if (args[1] == DIR_CODE)
	{
		*value2 = ft_reverse_bytes(&process->current[(process->index + 1) % MEM_SIZE], DIR_SIZE);
		process->index += DIR_SIZE;
		return (1);
	}
	else if (args[1] == IND_CODE)
	{
		index = ft_reverse_bytes(&process->current[(process->index + 1) % MEM_SIZE], IND_SIZE);
		*value2 = ft_reverse_bytes(&process->current[(process->index + index - size - 1) % MEM_SIZE], DIR_SIZE);
		process->index += IND_SIZE;
		return (1);
	}
	else
		return (0);
}


void	op_and(t_process *process)
{
	unsigned int	value1;
	unsigned int	value2;
	unsigned int	size1;
	unsigned int	size2;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(5);
	find_args(&process->current[++process->index % MEM_SIZE], args);
	ft_get_size(&size1, args[0]);
	ft_get_size(&size2, args[1]);
	if (args[0] && args[1] && args[2] == REG_CODE
	&& process->current[(process->index + size1 + size2 + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + size1 + size2 + 1) % MEM_SIZE] < 16)
	{
		if (!get_first_value(process, args, &value1))
			return ;
		if (!get_second_value(process, args, &value2))
			return ;
		process->reg[process->current[++process->index % MEM_SIZE]] = value1 & value2;
		process->duration += op_tab.cycles;
		if (!(value1 & value2) && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;
	}
}

void	op_or(t_process *process)
{
	unsigned int	value1;
	unsigned int	value2;
	unsigned int	size1;
	unsigned int	size2;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(6);
	find_args(&process->current[++process->index % MEM_SIZE], args);
	ft_get_size(&size1, args[0]);
	ft_get_size(&size2, args[1]);
	if (args[0] && args[1] && args[2] == REG_CODE
	&& process->current[(process->index + size1 + size2 + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + size1 + size2 + 1) % MEM_SIZE] < 16)
	{
		if (!get_first_value(process, args, &value1))
			return ;
		if (!get_second_value(process, args, &value2))
			return ;
		process->reg[process->current[++process->index % MEM_SIZE]] = value1 | value2;
		process->duration += op_tab.cycles;
		if (!(value1 | value2) && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;
	}
}

void	op_xor(t_process *process)
{
	unsigned int	value1;
	unsigned int	value2;
	unsigned int	size1;
	unsigned int	size2;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(7);
	find_args(&process->current[++process->index % MEM_SIZE], args);
	ft_get_size(&size1, args[0]);
	ft_get_size(&size2, args[1]);
	if (args[0] && args[1] && args[2] == REG_CODE
	&& process->current[(process->index + size1 + size2 + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + size1 + size2 + 1) % MEM_SIZE] < 16)
	{
		if (!get_first_value(process, args, &value1))
			return ;
		if (!get_second_value(process, args, &value2))
			return ;
		process->reg[process->current[++process->index % MEM_SIZE]] = value1 ^ value2;
		process->duration += op_tab.cycles;
		if (!(value1 ^ value2) && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;
	}
}

void	op_zjmp(t_process *process)
{
	t_op			op_tab;
	unsigned int	index;

	op_tab = ft_get_op(8);
	index = ft_reverse_bytes(&process->current[++process->index % MEM_SIZE], IND_SIZE);
	if (process->carry)
		process->index += ((index - 1) % MEM_SIZE) % IDX_MOD;
	process->duration += op_tab.cycles;
}

int		get_first_value_ind(t_process *process, t_arg_type *args, unsigned int *value1)
{
	unsigned int index;

	if (args[0] == REG_CODE
	&& process->current[(process->index + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + 1) % MEM_SIZE] < 16)
	{
		//dont need to reverse, just take the 2 bytes
		*value1 = ft_reverse_bytes(&process->reg[process->current[++process->index % MEM_SIZE]], IND_SIZE);
		return (1);
	}
	else if (args[0] == DIR_CODE)
	{
		*value1 = ft_reverse_bytes(&process->current[((process->index + 1) % MEM_SIZE) % IDX_MOD], IND_SIZE);
		process->index += IND_SIZE;
		return (1);
	}
	else if (args[0] == IND_CODE)
	{
		index = ft_reverse_bytes(&process->current[(process->index + 1) % MEM_SIZE], IND_SIZE);
		*value1 = ft_reverse_bytes(&process->current[((process->index + index - 1) % MEM_SIZE) % IDX_MOD], IND_SIZE);
		process->index += IND_SIZE;
		return (1);
	}
	else
		return (0);
}

int		get_second_value_ind(t_process *process, t_arg_type *args, unsigned int *value2)
{
	unsigned int	index;
	unsigned int	size;

	ft_get_size(&size, args[0]);
	if (args[1] == REG_CODE
	&& process->current[(process->index + 1) % MEM_SIZE] >= 0
	&& process->current[(process->index + 1) % MEM_SIZE] < 16)
	{
		// dont need to reverse, just take 2 bytes
		*value2 = ft_reverse_bytes(&process->reg[process->current[++process->index % MEM_SIZE]], IND_SIZE);
		return (1);
	}
	else if (args[1] == DIR_CODE)
	{
		*value2 = ft_reverse_bytes(&process->current[(process->index + 1) % MEM_SIZE], IND_SIZE);
		process->index += IND_SIZE;
		return (1);
	}
	else
		return (0);
}

void	op_ldi(t_process *process)
{
	unsigned int	size1;
	unsigned int	size2;
	unsigned int	value1;
	unsigned int	value2;
	unsigned int	total_value;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(9);
	find_args(&process->current[++process->index % MEM_SIZE], args);
	ft_get_size(&size1, args[0]);
	ft_get_size(&size2, args[1]);
	if (args[0] && (args[1] == DIR_CODE || args[1] == REG_CODE) && args[2] == REG_CODE
	&& process->current[(process->index + size1 + size2 + 1) % MEM_SIZE] > 0
	&& process->current[(process->index + size1 + size2 + 1) % MEM_SIZE] < 16) // change everywhere, regs from 1
	{
		if (!get_first_value_ind(process, args, &value1))
			return ;
		// reverse incrementation if second does not succeed or do not increment the first?? everywhere
		if (!get_second_value_ind(process, args, &value2))
			return ;
		total_value = ft_reverse_bytes(&process->current[((process->index - size1 - size2 - 1 + value1 + value2) % MEM_SIZE) % IDX_MOD], REG_SIZE);
		process->reg[process->current[(process->index + 1) % MEM_SIZE]] = total_value;
		process->duration += op_tab.cycles;
		if (!total_value && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;
	}
}

void	op_sti(t_process *process)
{
	unsigned int	size1;
	unsigned int	size2;
	unsigned int	value1;
	unsigned int	value2;
	unsigned int	total_value;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(10);
	find_args(&process->current[++process->index % MEM_SIZE], args);
	ft_get_size(&size1, args[0]);
	ft_get_size(&size2, args[1]);
	if (args[0] == REG_CODE &&  args[1] && (args[2] == DIR_CODE || args[2] == REG_CODE)
	&& process->current[(process->index + 1) % MEM_SIZE] > 0
	&& process->current[(process->index + 1) % MEM_SIZE] < 16) // change everywhere, regs from 1
	{
		process->index++;
		if (!get_first_value_ind(process, args, &value1))
			return ;
		// reverse incrementation if second does not succeed or do not increment the first?? everywhere
		if (!get_second_value_ind(process, args, &value2))
			return ;
		total_value = ft_reverse_bytes(&process->current[((process->index - size1 - size2 - 1 + value1 + value2) % MEM_SIZE) % IDX_MOD], REG_SIZE);
		process->current[((process->index - size1 - size2 - 1 + total_value) % MEM_SIZE) % IDX_MOD] = process->reg[(process->index - size1 - size2) % MEM_SIZE];
		process->duration += op_tab.cycles;
		if (!total_value && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;
	}
}