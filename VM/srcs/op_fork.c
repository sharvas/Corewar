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
	t_process	*fork;
	short		index;

	fork = ft_fork_process(game, process);
	ft_get_index(&game->arena[++process->index], IND_SIZE, &index);
	process->index++;
	fork->index += index;
}

void	op_lfork(t_game *game ,t_process *process)
{
	t_process	*fork;
	short		index;

	fork = ft_fork_process(game, process);
	index = ft_reverse_bytes(&game->arena[++process->index], IND_SIZE);
	process->index++;
	fork->index += index;
}