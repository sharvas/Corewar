/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 18:27:10 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/17 18:27:11 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		reset_live(t_game *game)
{
	int	i;

	i = 0;
	while (++i <= game->champ_total)
		game->champ[i].alive_count = 0;
	game->alive_count = 0;
}

int			add_duration(t_game *game, t_process *process)
{
	t_op			op_tab;
	unsigned char	index;

	index = game->arena[process->index];
	if (index > 0 && index < 17)
	{
		op_tab = get_op(index - 1);
		process->duration = op_tab.cycles;
		return (op_tab.cycles);
	}
	return (0);
}

int			count_process(t_game *game)
{
	t_process	*process;
	int			count;

	count = 0;
	process = game->process;
	while (process)
	{
		count++;
		process = process->next;
	}
	return (count);
}
