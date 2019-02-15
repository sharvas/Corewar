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

void	ft_fork_process(t_game *game, t_process *parent, short index)
{
	t_process	*new;
	t_process	*last;
	int			i;

	i = 0;
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		exit(1); //ft_error
	ft_bzero(new, sizeof(*new));
	new->index = ft_index_mod(parent->index + index);
	new->champ = parent->champ;
	new->alive = parent->alive;
	new->carry = parent->carry;
	while (++i <= REG_NUMBER)
		new->reg[i] = parent->reg[i];
	last = game->process;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	op_fork(t_game *game, t_process *process)
{
	short		index;

	ft_get_index(&game->arena[process->index + 1], IND_SIZE, &index);
	ft_fork_process(game, process, index);
	// ft_printf("FORK(%i) index: %i\n", process->champ, index);
	process->index += IND_SIZE;
}

void	op_lfork(t_game *game ,t_process *process)
{
	short		index;

	index = ft_reverse_bytes(&game->arena[process->index + 1], IND_SIZE);
	ft_fork_process(game, process, index);
	// ft_printf("LFORK(%i) index: %i\n", process->champ, index);
	process->index += IND_SIZE;
}