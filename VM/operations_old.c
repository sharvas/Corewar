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
		process->reg[game->arena[(process->index + DIR_SIZE) % MEM_SIZE]] = value;

		ft_printf("champ(%u): load (T_DIR %u, T_REG %u)\n", process->champ, value,
			game->arena[(process->index + DIR_SIZE) % MEM_SIZE]);
		
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

		ft_printf("champ(%u): load (T_IND %% IDX_MOD %u, T_REG %u)\n", process->champ, value,
			game->arena[(process->index + IND_SIZE) % MEM_SIZE]);
		
		process->reg[game->arena[(process->index + IND_SIZE) % MEM_SIZE]] = value;
		process->index += IND_SIZE;
		process->duration += op_tab.cycles;
		if (op_tab.carry)
			process->carry = 1;
	}
}

void	spread_color(int index, t_game *game, t_process *process)
{
	int	i;

	i = 0;
	while (i < 4)
		ft_memcpy(game->arena_champs + index + i++, &process->champ, 1);
}

void	op_st(t_game *game, t_process *process)
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
		ft_get_index(&game->arena[++process->index % MEM_SIZE], IND_SIZE, &index);
		
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

void	op_add(t_game *game, t_process *process)
{
	int			reg1;
	int			reg2;
	t_op		op_tab;
	t_arg_type	args[4];

	op_tab = ft_get_op(3);
	find_args(&game->arena[++process->index % MEM_SIZE], args);
	if (args[0] == REG_CODE && args[1] == REG_CODE && args[2] == REG_CODE
	&& game->arena[(process->index + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + 1) % MEM_SIZE] <= REG_NUMBER
	&& game->arena[(process->index + 2) % MEM_SIZE] >= 1
	&& game->arena[(process->index + 2) % MEM_SIZE] <= REG_NUMBER
	&& game->arena[(process->index + 3) % MEM_SIZE] >= 1
	&& game->arena[(process->index + 3) % MEM_SIZE] <= REG_NUMBER)
	{
		reg1 = process->reg[game->arena[++process->index % MEM_SIZE]];
		reg2 = process->reg[game->arena[++process->index % MEM_SIZE]];
		process->reg[game->arena[++process->index % MEM_SIZE]] = reg1 + reg2;
		process->duration += op_tab.cycles;
		if (reg1 + reg2 == 0 && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;

		ft_printf("champ (%i): add (T_REG %i, T_REG %i, T_REG %i) [carry - %i]\n", process->champ, 
			game->arena[(process->index - 3) % MEM_SIZE],
			game->arena[(process->index - 2) % MEM_SIZE],
			game->arena[(process->index - 1) % MEM_SIZE], process->carry);
	}
}

void	op_sub(t_game *game, t_process *process)
{
	int			reg1;
	int			reg2;
	t_op		op_tab;
	t_arg_type	args[4];

	op_tab = ft_get_op(4);
	// if args fail, need to process->index--;
	find_args(&game->arena[++process->index % MEM_SIZE], args);
	if (args[0] == REG_CODE && args[1] == REG_CODE && args[2] == REG_CODE
	&& game->arena[(process->index + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + 1) % MEM_SIZE] <= REG_NUMBER
	&& game->arena[(process->index + 2) % MEM_SIZE] >= 1
	&& game->arena[(process->index + 2) % MEM_SIZE] <= REG_NUMBER
	&& game->arena[(process->index + 3) % MEM_SIZE] >= 1
	&& game->arena[(process->index + 3) % MEM_SIZE] <= REG_NUMBER)
	{
		reg1 = process->reg[game->arena[++process->index % MEM_SIZE]];
		reg2 = process->reg[game->arena[++process->index % MEM_SIZE]];
		process->reg[game->arena[++process->index % MEM_SIZE]] = reg1 - reg2;
		process->duration += op_tab.cycles;
		if (reg1 - reg2 == 0 && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;

		ft_printf("champ (%i): add (T_REG %i, T_REG %i, T_REG %i) [carry - %i]\n", process->champ,
			game->arena[(process->index - 3) % MEM_SIZE],
			game->arena[(process->index - 2) % MEM_SIZE],
			game->arena[(process->index - 1) % MEM_SIZE], process->carry);
	}
}

void	ft_get_size(unsigned int *size, t_arg_type args, int i)
{
	if (args == REG_CODE)
		*size = T_REG;
	else if (args == IND_CODE)
		*size = IND_SIZE;
	else if (args == DIR_CODE)
		*size = DIR_SIZE / i;
	else
		*size = 0;
}

int		get_first_value(t_game *game, t_process *process, t_arg_type *args, int *value1)
{
	short index;

	if (args[0] == REG_CODE
	&& game->arena[(process->index + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		*value1 = process->reg[game->arena[++process->index % MEM_SIZE]];
		return (1);
	}
	else if (args[0] == DIR_CODE)
	{
		*value1 = ft_reverse_bytes(&game->arena[(process->index + 1) % MEM_SIZE], DIR_SIZE);
		process->index += DIR_SIZE;
		return (1);
	}
	else if (args[0] == IND_CODE)
	{
		ft_get_index(&game->arena[(process->index + 1) % MEM_SIZE], IND_SIZE, &index);
		*value1 = ft_reverse_bytes(&game->arena[(process->index + index - 1) % MEM_SIZE], DIR_SIZE);
		process->index += IND_SIZE;
		return (1);
	}
	else
		return (0);
}

int		get_second_value(t_game *game, t_process *process, t_arg_type *args, int *value2)
{
	short			index;
	unsigned int	size;

	ft_get_size(&size, args[0], 1);
	if (args[1] == REG_CODE
	&& game->arena[(process->index + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		*value2 = process->reg[game->arena[++process->index % MEM_SIZE]];
		return (1);
	}
	else if (args[1] == DIR_CODE)
	{
		*value2 = ft_reverse_bytes(&game->arena[(process->index + 1) % MEM_SIZE], DIR_SIZE);
		process->index += DIR_SIZE;
		return (1);
	}
	else if (args[1] == IND_CODE)
	{
		ft_get_index(&game->arena[(process->index + 1) % MEM_SIZE], IND_SIZE, &index);
		*value2 = ft_reverse_bytes(&game->arena[(process->index + index - size - 1) % MEM_SIZE], DIR_SIZE);
		process->index += IND_SIZE;
		return (1);
	}
	else
		return (0);
}

void	op_and(t_game *game, t_process *process)
{
	int				value1;
	int				value2;
	unsigned int	size1;
	unsigned int	size2;
	t_op			op_tab;
	t_arg_type		args[4];

	op_tab = ft_get_op(5);
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

void	op_zjmp(t_game *game, t_process *process)
{
	t_op	op_tab;
	short	index;
	short	sign;

	op_tab = ft_get_op(8);
	sign = 1;
	ft_get_index(&game->arena[++process->index % MEM_SIZE], IND_SIZE, &index);
	if (process->carry)
		process->index += sign * ((index % IDX_MOD) % MEM_SIZE) - 2;
	process->duration += op_tab.cycles;
}

int		get_first_value_ind(t_game *game, t_process *process, t_arg_type args, short *value1)
{
	short index;

	if (args == REG_CODE
	&& game->arena[(process->index + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		*value1 = *(short *)(process->reg + game->arena[++process->index % MEM_SIZE]);
		return (1);
	}
	else if (args == DIR_CODE)
	{
		*value1 = ft_reverse_bytes(&game->arena[(process->index + 1) % MEM_SIZE], IND_SIZE);
		process->index += IND_SIZE;
		return (1);
	}
	else if (args == IND_CODE)
	{
		ft_get_index(&game->arena[(process->index + 1) % MEM_SIZE], IND_SIZE, &index);
		*value1 = ft_reverse_bytes(&game->arena[(process->index - 1 + index ) % MEM_SIZE], IND_SIZE);
		process->index += IND_SIZE;
		return (1);
	}
	else
		return (0);
}

int		get_second_value_ind(t_game *game, t_process *process, t_arg_type args, short *value2)
{
	if (args == REG_CODE
	&& game->arena[(process->index + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->index + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		*value2 = *(short *)(process->reg + game->arena[++process->index % MEM_SIZE]);
		return (1);
	}
	else if (args == DIR_CODE)
	{
		*value2 = ft_reverse_bytes(&game->arena[(process->index + 1) % MEM_SIZE], IND_SIZE);
		process->index += IND_SIZE;
		return (1);
	}
	else
		return (0);
}

void	op_ldi(t_game *game, t_process *process)
{
	unsigned int	size1;
	unsigned int	size2;
	short			value1;
	short			value2;
	short			total_index;
	int				total_value;
	int				sign;
	t_op			op_tab;
	t_arg_type		args[4];

	sign = 1;
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
		if (total_index < 0)
		{
			sign = -1;
			total_index = -total_index;
		}
		total_index = (total_index % IDX_MOD) * sign;
		total_value = ft_reverse_bytes(&game->arena[(process->index - size1 - size2 - 1
			+ total_index) % MEM_SIZE], REG_SIZE);
		process->reg[game->arena[(process->index + 1) % MEM_SIZE]] = total_value;
		process->duration += op_tab.cycles;
		if (total_value == 0 && op_tab.carry)
			process->carry = 1;
		else if (op_tab.carry)
			process->carry = 0;
	}
}

void	op_sti(t_game *game, t_process *process)
{
	unsigned int	size1;
	unsigned int	size2;
	short			value1;
	short			value2;
	short			total_index;
	int				sign;
	t_op			op_tab;
	t_arg_type		args[4];

	sign = 1;
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
		total_index = value1 + value2;
		if (total_index < 0)
		{
			sign = -1;
			total_index = -total_index;
		}
		total_index = (total_index % IDX_MOD) * sign;
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

// void	op_fork(t_process *process, t_game *game)
// {
// 	t_op			op_tab;

// 	t_process *new;
// 	t_process *last;
// 	// int			i;

// 	op_tab = ft_get_op(11);
// 	// i = 0;
// 	// if (!(new = (t_process *)malloc(sizeof(t_process))))
// 	// 	exit(1); //ft_error
// 	// ft_bzero(new, sizeof(*new));
// 	// new->current = process->current;//?
// 	// new->index = process->index;// + (index % IDX_MOD) % MEM_SIZE
// 	// new->champ = process->champ;
// 	// new->alive = process->alive;
// 	// while (++i <= 16)
// 	// 	new->reg[i] = process->reg[i];
// 	new->duration += op_tab.cycles;//??

// 	last = game->process;//add to end like this?
// 	// while (last->next)//add to end like this?
// 	// 	last = last->next;//add to end like this?
// 	// last->next = new;//add to end like this?
// }

void	op_lld(t_process *process)
{
	t_op			op_tab;

	op_tab = ft_get_op(12);
	process->duration += op_tab.cycles;//
}

void	op_lldi(t_process *process)
{
	t_op			op_tab;

	op_tab = ft_get_op(13);
	process->duration += op_tab.cycles;//
}

void	op_lfork(t_process *process)
{
	t_op			op_tab;

	op_tab = ft_get_op(14);
	process->duration += op_tab.cycles;//
}

void	op_aff(t_process *process)
{
	t_op			op_tab;

	op_tab = ft_get_op(15);
	process->duration += op_tab.cycles;//
}