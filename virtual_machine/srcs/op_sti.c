/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 18:42:09 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/17 18:42:12 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		color(int index, t_game *game, t_process *process)
{
	int	i;

	i = 0;
	while (i < 4)
		ft_memcpy(game->arena_champs + ((index + i++) % MEM_SIZE),
		&process->champ, 1);
}

static void	print_op_sti(t_game *game, t_process *process, unsigned char reg_id,
int *value)
{
	if (game->flag_op)
		ft_printf("STI(%i) reg_id: %i, value1: %i, value2: %i\n",
		process->champ, reg_id, value[0], value[1]);
}

static void	op_sti_args(t_game *game, t_process *process, t_arg_type *args,
unsigned int *size)
{
	find_args(&game->arena[++process->seek % MEM_SIZE], args, game->flag_arg);
	get_size(&size[0], args[1], 2);
	get_size(&size[1], args[2], 2);
}

void		op_sti(t_game *game, t_process *process)
{
	unsigned int	size[2];
	unsigned char	reg_id;
	int				value[2];
	short			t_idx;
	t_arg_type		args[4];

	process->seek = process->index;
	op_sti_args(game, process, args, size);
	if (args[0] == REG_CODE && args[1] && (args[2] == DIR_CODE
	|| args[2] == REG_CODE) && check_args(game, process->seek, args, 11))
	{
		reg_id = game->arena[++process->seek % MEM_SIZE];
		get_first_value_ind_sti(game, process, args[1], &value[0]);
		get_second_value_ind(game, process, args[2], &value[1]);
		index_sum(value[0], value[1], &t_idx);
		*(int *)(game->arena + (index_mod(process->seek - size[0] - size[1]
			- 2 + t_idx) % MEM_SIZE)) = reverse_bytes(&process->reg[reg_id],
			REG_SIZE);
		print_op_sti(game, process, reg_id, value);
		color((index_mod(process->seek - size[0] - size[1] - 2 + t_idx)
			% MEM_SIZE), game, process);
		process->index = process->seek;
	}
	else
		process->index = move_index(process->index, args, 11);
}
