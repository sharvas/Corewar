/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 16:44:23 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/17 16:44:27 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_add(t_game *game, t_process *process)
{
	int			reg1;
	int			reg2;
	t_arg_type	args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args, game->flag_arg);
	if (args[0] == REG_CODE && args[1] == REG_CODE && args[2] == REG_CODE
	&& check_args(game, process->seek, args, 4))
	{
		reg1 = process->reg[game->arena[++process->seek % MEM_SIZE]];
		reg2 = process->reg[game->arena[++process->seek % MEM_SIZE]];
		process->reg[game->arena[++process->seek % MEM_SIZE]] = reg1 + reg2;
		if (game->flag_op)
			ft_printf("ADD(%i) value1: %i, value2: %i, reg3: %i \n",
			process->champ, reg1, reg2, game->arena[process->seek % MEM_SIZE]);
		if (reg1 + reg2 == 0)
			process->carry = 1;
		else
			process->carry = 0;
		process->index = process->seek;
	}
	else
		process->index = move_index(process->index, args, 4);
}

void	op_sub(t_game *game, t_process *process)
{
	int			reg1;
	int			reg2;
	t_arg_type	args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args, game->flag_arg);
	if (args[0] == REG_CODE && args[1] == REG_CODE && args[2] == REG_CODE
	&& check_args(game, process->seek, args, 5))
	{
		reg1 = process->reg[game->arena[++process->seek % MEM_SIZE]];
		reg2 = process->reg[game->arena[++process->seek % MEM_SIZE]];
		process->reg[game->arena[++process->seek % MEM_SIZE]] = reg1 - reg2;
		if (game->flag_op)
			ft_printf("SUB(%i) value1: %i, value2: %i, reg3: %i\n",
			process->champ, reg1, reg2, game->arena[process->seek % MEM_SIZE]);
		if (reg1 - reg2 == 0)
			process->carry = 1;
		else
			process->carry = 0;
		process->index = process->seek;
	}
	else
		process->index = move_index(process->index, args, 5);
}
