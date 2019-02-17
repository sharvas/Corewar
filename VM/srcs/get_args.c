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

void	get_first_value(t_game *game, t_process *process, t_arg_type *args,
int *value1)
{
	short index;

	if (args[0] == REG_CODE)
		*value1 = process->reg[game->arena[++process->seek % MEM_SIZE]];
	else if (args[0] == DIR_CODE)
	{
		*value1 = ft_reverse_bytes(&game->arena[(process->seek + 1)
		% MEM_SIZE], DIR_SIZE);
		process->seek += DIR_SIZE;
	}
	else if (args[0] == IND_CODE)
	{
		ft_get_index(&game->arena[(process->seek + 1) % MEM_SIZE], IND_SIZE,
		&index);
		*value1 = ft_reverse_bytes(&game->arena[index_mod(process->seek - 1
		+ index) % MEM_SIZE], DIR_SIZE);
		process->seek += IND_SIZE;
	}
}

void	get_second_value(t_game *game, t_process *process, t_arg_type *args,
int *value2)
{
	short			index;
	unsigned int	size;

	ft_get_size(&size, args[0], 1);
	if (args[1] == REG_CODE)
		*value2 = process->reg[game->arena[++process->seek % MEM_SIZE]];
	else if (args[1] == DIR_CODE)
	{
		*value2 = ft_reverse_bytes(&game->arena[(process->seek + 1)
		% MEM_SIZE], DIR_SIZE);
		process->seek += DIR_SIZE;
	}
	else if (args[1] == IND_CODE)
	{
		ft_get_index(&game->arena[(process->seek + 1) % MEM_SIZE],
		IND_SIZE, &index);
		*value2 = ft_reverse_bytes(&game->arena[index_mod(process->seek
		- size - 1 + index) % MEM_SIZE], DIR_SIZE);
		process->seek += IND_SIZE;
	}
}

void	get_first_value_ind(t_game *game, t_process *process, t_arg_type args,
int *value1)
{
	short index;

	if (args == REG_CODE)
		*value1 =
		*(short *)(process->reg + game->arena[++process->seek % MEM_SIZE]);
	else if (args == DIR_CODE)
	{
		*value1 =
		ft_reverse_bytes(&game->arena[++process->seek % MEM_SIZE], IND_SIZE);
		process->seek++;
	}
	else if (args == IND_CODE)
	{
		index = ft_reverse_bytes(&game->arena[(process->seek + 1)
		% MEM_SIZE], IND_SIZE);
		*value1 = ft_reverse_bytes(&game->arena[index_mod(process->seek
		- 1 + index) % MEM_SIZE], DIR_SIZE);
		process->seek += IND_SIZE;
	}
}

void	get_second_value_ind(t_game *game, t_process *process,
t_arg_type args, int *value2)
{
	if (args == REG_CODE)
		*value2 = *(short *)(process->reg
		+ game->arena[++process->seek % MEM_SIZE]);
	else if (args == DIR_CODE)
	{
		*value2 = ft_reverse_bytes(&game->arena[++process->seek
		% MEM_SIZE], IND_SIZE);
		process->seek++;
	}
}
