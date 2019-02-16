/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:48:06 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/13 11:48:15 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_add(t_game *game, t_process *process)
{
	int			reg1;
	int			reg2;
	t_arg_type	args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args);
	if (args[0] == REG_CODE && args[1] == REG_CODE && args[2] == REG_CODE
	&& game->arena[(process->seek + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->seek + 1) % MEM_SIZE] <= REG_NUMBER
	&& game->arena[(process->seek + 2) % MEM_SIZE] >= 1
	&& game->arena[(process->seek + 2) % MEM_SIZE] <= REG_NUMBER
	&& game->arena[(process->seek + 3) % MEM_SIZE] >= 1
	&& game->arena[(process->seek + 3) % MEM_SIZE] <= REG_NUMBER)
	{
		reg1 = process->reg[game->arena[++process->seek % MEM_SIZE]];
		reg2 = process->reg[game->arena[++process->seek % MEM_SIZE]];
		process->reg[game->arena[++process->seek % MEM_SIZE]] = reg1 + reg2;
		if (game->flag_op)
			ft_printf("ADD(%i) reg1: %i, reg2: %i, sum: %i\n", process->champ, reg1, reg2, reg1 + reg2);
		if (reg1 + reg2 == 0)
			process->carry = 1;
		else
			process->carry = 0;
		process->index = process->seek;
	}
	else
		process->index = ft_move_index(process->index, args, 4);
}

void	op_sub(t_game *game, t_process *process)
{
	int			reg1;
	int			reg2;
	t_arg_type	args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args);
	if (args[0] == REG_CODE && args[1] == REG_CODE && args[2] == REG_CODE
	&& game->arena[(process->seek + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->seek + 1) % MEM_SIZE] <= REG_NUMBER
	&& game->arena[(process->seek + 2) % MEM_SIZE] >= 1
	&& game->arena[(process->seek + 2) % MEM_SIZE] <= REG_NUMBER
	&& game->arena[(process->seek + 3) % MEM_SIZE] >= 1
	&& game->arena[(process->seek + 3) % MEM_SIZE] <= REG_NUMBER)
	{
		reg1 = process->reg[game->arena[++process->seek % MEM_SIZE]];
		reg2 = process->reg[game->arena[++process->seek % MEM_SIZE]];
		process->reg[game->arena[++process->seek % MEM_SIZE]] = reg1 - reg2;
		if (game->flag_op)
			ft_printf("SUB(%i) reg1: %i, reg2: %i, sum: %i\n", process->champ, reg1, reg2, reg1 - reg2);
		if (reg1 - reg2 == 0)
			process->carry = 1;
		else
			process->carry = 0;
		process->index = process->seek;
	}
	else
		process->index = ft_move_index(process->index, args, 5);
}