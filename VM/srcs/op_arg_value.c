/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arg_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:56:01 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/13 11:56:02 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
		index = ft_reverse_bytes(&game->arena[(process->index + 1) % MEM_SIZE], IND_SIZE) % IDX_MOD;
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
		index = ft_reverse_bytes(&game->arena[(process->index + 1) % MEM_SIZE], IND_SIZE) % IDX_MOD;
		*value2 = ft_reverse_bytes(&game->arena[(process->index + index - size - 1) % MEM_SIZE], DIR_SIZE);
		process->index += IND_SIZE;
		return (1);
	}
	else
		return (0);
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
		index = ft_reverse_bytes(&game->arena[(process->index + 1) % MEM_SIZE], IND_SIZE) % IDX_MOD;
		*value1 = ft_reverse_bytes(&game->arena[(process->index - 1 + index ) % MEM_SIZE], IND_SIZE);
		process->index += IND_SIZE;
		return (1);
	}
	else
		return (0);
}

int		get_second_value_ind(t_game *game, t_process *process, t_arg_type args, short *value2)
{
	// short index;

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