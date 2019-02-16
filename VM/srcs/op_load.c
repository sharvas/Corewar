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
	t_arg_type	args[4];

	process->seek_index = process->index;
	find_args(&game->arena[++process->seek_index % MEM_SIZE], args, game->flag_arg);
	if (args[0] == DIR_CODE && args[1] == REG_CODE
	&& game->arena[(process->seek_index + DIR_SIZE + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->seek_index + DIR_SIZE + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		value = ft_reverse_bytes(&game->arena[++process->seek_index % MEM_SIZE], DIR_SIZE);
		process->reg[game->arena[(process->seek_index + DIR_SIZE) % MEM_SIZE]] = value;
		if (game->flag_op)
			ft_printf("LD(%i) value: %i, reg: %i\n", process->champ, value, game->arena[(process->seek_index + DIR_SIZE) % MEM_SIZE]);
		process->seek_index += DIR_SIZE;
		process->carry = 1;
		process->index = process->seek_index;
	}
	else if (args[0] == IND_CODE && args[1] == REG_CODE
	&& game->arena[(process->seek_index + IND_SIZE + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->seek_index + IND_SIZE + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		ft_get_index(&game->arena[++process->seek_index % MEM_SIZE], IND_SIZE, &index);
		value = ft_reverse_bytes(&game->arena[ft_index_mod(process->seek_index - 2 + index) % MEM_SIZE], DIR_SIZE);
		process->reg[game->arena[(process->seek_index + IND_SIZE) % MEM_SIZE]] = value;
		if (game->flag_op)
			ft_printf("LD(%i) value: %i, reg: %i\n", process->champ, value, game->arena[(process->seek_index + IND_SIZE) % MEM_SIZE]);
		process->seek_index += IND_SIZE;
		process->carry = 1;
		process->index = process->seek_index;
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
	t_arg_type		args[4];

	process->seek_index = process->index;
	find_args(&game->arena[++process->seek_index % MEM_SIZE], args, game->flag_arg);
	ft_get_size(&size1, args[0], 1);
	ft_get_size(&size2, args[1], 1);
	if (args[0] && (args[1] == DIR_CODE || args[1] == REG_CODE) && args[2] == REG_CODE
	&& game->arena[(process->seek_index + size1 + size2 + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->seek_index + size1 + size2 + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		if (!get_first_value_ind(game, process, args[0], &value1))
			return ;
		if (!get_second_value_ind(game, process, args[1], &value2))
			return ;
		ft_index_sum(value1, value2, &total_index);
		total_value = ft_reverse_bytes(&game->arena[ft_index_mod(process->seek_index - 1 - size1
			- size2 + total_index) % MEM_SIZE], REG_SIZE);
		process->reg[game->arena[++process->seek_index % MEM_SIZE]] = total_value;
		if (game->flag_op)
			ft_printf("LDI(%i) value: %i, reg: %i\n", process->champ, total_value, game->arena[(process->seek_index - 1) % MEM_SIZE]);
		if (total_value == 0)
			process->carry = 1;
		else
			process->carry = 0;
		process->index = process->seek_index;
	}
}

void	op_lld(t_game *game, t_process *process)
{
	int			value;
	short		index;
	t_arg_type	args[4];

	process->seek_index = process->index;
	find_args(&game->arena[++process->seek_index % MEM_SIZE], args, game->flag_arg);
	if (args[0] == DIR_CODE && args[1] == REG_CODE
	&& game->arena[(process->seek_index + DIR_SIZE + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->seek_index + DIR_SIZE + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		value = ft_reverse_bytes(&game->arena[++process->seek_index % MEM_SIZE], DIR_SIZE);
		process->reg[game->arena[(process->seek_index + DIR_SIZE) % MEM_SIZE]] = value;
		if (game->flag_op)
			ft_printf("LLD(%i) value: %i, reg: %i\n",process->champ, value, game->arena[(process->seek_index + DIR_SIZE) % MEM_SIZE]);
		process->seek_index += DIR_SIZE;
		process->carry = 1;
		process->index = process->seek_index;
	}
	else if (args[0] == IND_CODE && args[1] == REG_CODE
	&& game->arena[(process->seek_index + IND_SIZE + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->seek_index + IND_SIZE + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		index = ft_reverse_bytes(&game->arena[++process->seek_index % MEM_SIZE], IND_SIZE);
		value = ft_reverse_bytes(&game->arena[ft_index_mod(process->seek_index - 2 + index) % MEM_SIZE], IND_SIZE);
		process->reg[game->arena[(process->seek_index + IND_SIZE) % MEM_SIZE]] = value;
		if (game->flag_op)
			ft_printf("LLD(%i) value: %i, reg: %i\n",process->champ, value, game->arena[(process->seek_index + IND_SIZE) % MEM_SIZE]);
		process->seek_index += IND_SIZE;
		process->carry = 1;
		process->index = process->seek_index;
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
	t_arg_type		args[4];

	process->seek_index = process->index;
	find_args(&game->arena[++process->seek_index % MEM_SIZE], args, game->flag_arg);
	ft_get_size(&size1, args[0], 1);
	ft_get_size(&size2, args[1], 1);
	if (args[0] && (args[1] == DIR_CODE || args[1] == REG_CODE) && args[2] == REG_CODE
	&& game->arena[(process->seek_index + size1 + size2 + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->seek_index + size1 + size2 + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		if (!get_first_value_ind(game, process, args[0], &value1))
			return ;
		if (!get_second_value_ind(game, process, args[1], &value2))
			return ;
		total_index = value1 + value2;
		total_value = ft_reverse_bytes(&game->arena[ft_index_mod(process->seek_index - 1 - size1
			- size2 + total_index) % MEM_SIZE], REG_SIZE);
		process->reg[game->arena[++process->seek_index % MEM_SIZE]] = total_value;
		if (game->flag_op)
			ft_printf("LLDI(%i) value: %i, reg: %i\n",process->champ, total_value, game->arena[(process->seek_index - 1) % MEM_SIZE]);
		if (total_value == 0)
			process->carry = 1;
		else
			process->carry = 0;
		process->index = process->seek_index;
	}
}