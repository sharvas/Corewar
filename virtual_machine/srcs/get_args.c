/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 11:53:38 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/18 11:53:41 by dfinnis          ###   ########.fr       */
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
		*value1 = reverse_bytes(&game->arena[(process->seek + 1)
			% MEM_SIZE], DIR_SIZE);
		process->seek += DIR_SIZE;
	}
	else if (args[0] == IND_CODE)
	{
		get_index(&game->arena[(process->seek + 1) % MEM_SIZE], IND_SIZE,
			&index);
		*value1 = reverse_bytes(&game->arena[index_mod(process->seek - 1
			+ index) % MEM_SIZE], DIR_SIZE);
		process->seek += IND_SIZE;
	}
}

void	get_second_value(t_game *game, t_process *process, t_arg_type *args,
int *value2)
{
	short			index;
	unsigned int	size;

	get_size(&size, args[0], 1);
	if (args[1] == REG_CODE)
		*value2 = process->reg[game->arena[++process->seek % MEM_SIZE]];
	else if (args[1] == DIR_CODE)
	{
		*value2 = reverse_bytes(&game->arena[(process->seek + 1)
			% MEM_SIZE], DIR_SIZE);
		process->seek += DIR_SIZE;
	}
	else if (args[1] == IND_CODE)
	{
		get_index(&game->arena[(process->seek + 1) % MEM_SIZE],
			IND_SIZE, &index);
		*value2 = reverse_bytes(&game->arena[index_mod(process->seek
			- size - 1 + index) % MEM_SIZE], DIR_SIZE);
		process->seek += IND_SIZE;
	}
}

void	get_first_value_ind_sti(t_game *game, t_process *process,
t_arg_type args, int *value1)
{
	short index;

	if (args == REG_CODE)
		*value1 = *(short *)(process->reg
		+ game->arena[++process->seek % MEM_SIZE]);
	else if (args == DIR_CODE)
	{
		*value1 = reverse_bytes(&game->arena[++process->seek
			% MEM_SIZE], IND_SIZE);
		process->seek++;
	}
	else if (args == IND_CODE)
	{
		index = reverse_bytes(&game->arena[(process->seek + 1)
			% MEM_SIZE], IND_SIZE);
		*value1 = reverse_bytes(&game->arena[index_mod(process->seek
			- 2 + index) % MEM_SIZE], DIR_SIZE);
		process->seek += IND_SIZE;
	}
}

void	get_first_value_ind(t_game *game, t_process *process, t_arg_type args,
int *value1)
{
	short index;

	if (args == REG_CODE)
		*value1 = *(short *)(process->reg
		+ game->arena[++process->seek % MEM_SIZE]);
	else if (args == DIR_CODE)
	{
		*value1 = reverse_bytes(&game->arena[++process->seek
			% MEM_SIZE], IND_SIZE);
		process->seek++;
	}
	else if (args == IND_CODE)
	{
		index = reverse_bytes(&game->arena[(process->seek + 1)
			% MEM_SIZE], IND_SIZE);
		*value1 = reverse_bytes(&game->arena[index_mod(process->seek
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
		*value2 = reverse_bytes(&game->arena[++process->seek
			% MEM_SIZE], IND_SIZE);
		process->seek++;
	}
}
