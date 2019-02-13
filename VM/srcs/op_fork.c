/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:58:15 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/13 11:58:16 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// void	op_fork(t_game *game, t_process *process)
// {
// 	t_op			op_tab;

// 	t_process *new;
// 	t_process *last;
// 	// int			i;

// 	op_tab = ft_get_op(11);
// 	// i = 0;
// 	// if (!(new = (t_process *)malloc(sizeof(t_process))))
// 	// 	exit(1); //ft_error
// 	// ft_bzero(new, sizeof(*new));
// 	// new->current = process->current;//?
// 	// new->index = process->index;// + (index % IDX_MOD) % MEM_SIZE
// 	// new->champ = process->champ;
// 	// new->alive = process->alive;
// 	// while (++i <= 16)
// 	// 	new->reg[i] = process->reg[i];
// 	new->duration += op_tab.cycles;//??

// 	last = game->process;//add to end like this?
// 	// while (last->next)//add to end like this?
// 	// 	last = last->next;//add to end like this?
// 	// last->next = new;//add to end like this?
// }

void	op_lfork(t_process *process)
{
	t_op			op_tab;

	op_tab = ft_get_op(14);
	process->duration += op_tab.cycles;//
}