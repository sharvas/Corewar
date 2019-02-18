/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 18:41:00 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/17 18:41:05 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_op_st_idx(t_game *game, t_process *process,
unsigned char reg_index, short idx)
{
	if (game->flag_op)
		ft_printf("ST(%i) reg_id: %i, index: %i\n",
		process->champ, reg_index, idx);
}

static void	op_st_reg(t_game *game, t_process *process,
unsigned char *reg_index)
{
	*reg_index = game->arena[++process->seek % MEM_SIZE];
	process->reg[game->arena[++process->seek
		% MEM_SIZE]] = process->reg[*reg_index];
	process->carry = (!process->reg[*reg_index]) ? 1 : 0;
	if (game->flag_op)
		ft_printf("ST(%i) reg_id: %i, reg_id: %i\n",
		process->champ, *reg_index, game->arena[process->seek % MEM_SIZE]);
	process->index = process->seek;
}

void		op_st(t_game *game, t_process *process)
{
	short			idx;
	unsigned char	reg_index;
	t_arg_type		args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args, game->flag_arg);
	if (args[0] == REG_CODE && args[1] == IND_CODE
	&& check_args(game, process->seek, args, 3))
	{
		reg_index = game->arena[++process->seek % MEM_SIZE];
		get_index(&game->arena[++process->seek % MEM_SIZE], IND_SIZE, &idx);
		*(int *)(game->arena + (index_mod(process->seek - 3 + idx)
		% MEM_SIZE)) = reverse_bytes(&process->reg[reg_index], DIR_SIZE);
		print_op_st_idx(game, process, reg_index, idx);
		color(index_mod(process->seek - 3 + idx) % MEM_SIZE, game, process);
		process->index = process->seek + 1;
		process->carry = (!process->reg[reg_index]) ? 1 : 0;
	}
	else if (args[0] == REG_CODE && args[1] == REG_CODE
	&& check_args(game, process->seek, args, 3))
		op_st_reg(game, process, &reg_index);
	else
		process->index = move_index(process->index, args, 3);
}
