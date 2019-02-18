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

static void	ft_fork_process(t_game *game, t_process *parent, short index)
{
	t_process	*new;
	t_process	*last;
	int			i;

	i = 0;
	if (!(new = (t_process *)malloc(sizeof(t_process))))
		error_exit("malloc fail in ft_fork_process", game);
	ft_bzero(new, sizeof(*new));
	new->index = index_mod(parent->index + index);
	new->champ = parent->champ;
	new->alive = parent->alive;
	new->carry = parent->carry;
	while (++i <= REG_NUMBER)
		new->reg[i] = parent->reg[i];
	last = game->process;
	game->process = new;
	game->process->next = last;
}

void		op_fork(t_game *game, t_process *process)
{
	short		index;

	get_index(&game->arena[process->index + 1], IND_SIZE, &index);
	ft_fork_process(game, process, index);
	if (game->flag_op)
		ft_printf("FORK(%i) index: %i\n", process->champ, index);
	process->index += IND_SIZE;
}

void		op_lfork(t_game *game, t_process *process)
{
	short		index;

	index = reverse_bytes(&game->arena[process->index + 1], IND_SIZE);
	ft_fork_process(game, process, index);
	if (game->flag_op)
		ft_printf("LFORK(%i) index: %i\n", process->champ, index);
	process->index += IND_SIZE;
}
