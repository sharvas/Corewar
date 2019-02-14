/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_others.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 13:09:57 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/13 13:09:58 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_live(t_game *game, t_process *process)
{
	int		id;
	t_op	op_tab;

	op_tab = ft_get_op(0);
	id = ft_reverse_bytes(&game->arena[(process->index + 1) % MEM_SIZE], DIR_SIZE);
	process->alive = 1;
	process->duration += op_tab.cycles;
	if (id > 0 && id <= game->champ_count)
	{
		if (game->alive < 21)
			game->alive++;
		game->champ[id].alive++;
		game->champ[id].last_alive = game->cycle_count;
		if (!game->flag_v)
			ft_printf("A process shows that player %i (%s) is alive\n", game->champ[id].nbr, game->champ[id].header.prog_name);
	}
	process->index += DIR_SIZE;
}

void	op_zjmp(t_game *game, t_process *process)
{
	t_op	op_tab;
	short	index;

	op_tab = ft_get_op(8);
	ft_get_index(&game->arena[++process->index % MEM_SIZE], IND_SIZE, &index);
	if (process->carry)
		process->index += (index % MEM_SIZE) - 2;
	process->duration += op_tab.cycles;
}

void	op_aff(t_game *game, t_process *process)
{
	t_op			op_tab;

	op_tab = ft_get_op(15);
	process->duration += op_tab.cycles;//
}