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

void	op_fork(t_game *game, t_process *process)
{
	short		index;

	ft_get_index(&game->arena[process->index + 1], IND_SIZE, &index);
	ft_fork_process(game, process, index);
	ft_printf("FORK(%i) index: %i\n", process->champ, index);
	process->index += IND_SIZE;
}

void	op_lfork(t_game *game ,t_process *process)
{
	short		index;

	index = ft_reverse_bytes(&game->arena[process->index + 1], IND_SIZE);
	ft_fork_process(game, process, index);
	ft_printf("LFORK(%i) index: %i\n", process->champ, index);
	process->index += IND_SIZE;
}