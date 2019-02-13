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

		// ft_printf("champ (%i): add (T_REG %i, T_REG %i, T_REG %i) [carry - %i]\n", process->champ, 
		// 	game->arena[(process->index - 3) % MEM_SIZE],
		// 	game->arena[(process->index - 2) % MEM_SIZE],
		// 	game->arena[(process->index - 1) % MEM_SIZE], process->carry);
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

		// ft_printf("champ (%i): add (T_REG %i, T_REG %i, T_REG %i) [carry - %i]\n", process->champ,
		// 	game->arena[(process->index - 3) % MEM_SIZE],
		// 	game->arena[(process->index - 2) % MEM_SIZE],
		// 	game->arena[(process->index - 1) % MEM_SIZE], process->carry);
	}
}