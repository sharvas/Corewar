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
		ft_memcpy(game->arena_champs + ((index + i++) % MEM_SIZE), &process->champ, 1);
}

void	    op_st(t_game *game, t_process *process)
{
	short			index;
	unsigned char	reg_index;
	t_arg_type		args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args, game->flag_arg);
	if (args[0] == REG_CODE && args[1] == IND_CODE
	&& ft_check_args(game, process->seek, args, 3))
	{
		reg_index = game->arena[++process->seek % MEM_SIZE];
		ft_get_index(&game->arena[++process->seek % MEM_SIZE], IND_SIZE, &index);
		*(int *)(game->arena + (ft_index_mod(process->seek - 3 + index) % MEM_SIZE)) = ft_reverse_bytes(&process->reg[reg_index], DIR_SIZE);
		if (game->flag_op)
			ft_printf("ST(%i) reg_id: %i, index: %i\n", process->champ, reg_index, index);
		spread_color(ft_index_mod(process->seek - 3 + index) % MEM_SIZE, game, process);
		process->index = process->seek + 1;
	}
	else if (args[0] == REG_CODE && args[1] == REG_CODE
	&& ft_check_args(game, process->seek, args, 3))
	{
		reg_index = game->arena[++process->seek % MEM_SIZE];
		process->reg[game->arena[++process->seek % MEM_SIZE]] = process->reg[reg_index];
		if (game->flag_op)
			ft_printf("ST(%i) reg_id: %i, reg_id: %i\n", process->champ, reg_index, game->arena[process->seek % MEM_SIZE]);
		process->index = process->seek;
	}
	else
		process->index = ft_move_index(process->index, args, 3);
}

void	    op_sti(t_game *game, t_process *process)
{
	unsigned int	size[2];
	unsigned char	reg_id;
	int				value[2];
	short			total_index;
	t_arg_type		args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args, game->flag_arg);
	ft_get_size(&size[0], args[1], 2);
	ft_get_size(&size[1], args[2], 2);
	if (args[0] == REG_CODE && args[1] && (args[2] == DIR_CODE || args[2] == REG_CODE)
	&& ft_check_args(game, process->seek, args, 11))
	{
		reg_id = game->arena[++process->seek % MEM_SIZE];
		get_first_value_ind(game, process, args[1], &value[0]);
		get_second_value_ind(game, process, args[2], &value[1]);
		ft_index_sum(value[0], value[1], &total_index);
		*(int *)(game->arena + (ft_index_mod(process->seek - size[0] - size[1] - 2 + total_index) % MEM_SIZE))
		= ft_reverse_bytes(&process->reg[reg_id], REG_SIZE);
		if (game->flag_op)
			ft_printf("STI(%i) reg_id: %i, value1: %i, value2: %i\n", process->champ, reg_id, value[0], value[1]);
		spread_color((ft_index_mod(process->seek - size[0] - size[1] - 2 + total_index) % MEM_SIZE), game, process);
		process->index = process->seek;
	}
	else
		process->index = ft_move_index(process->index, args, 11);
}