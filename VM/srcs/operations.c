/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:44:35 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_live(t_game *game, t_op *op_tab, t_process *process)
{
	int id;

	id = *process->current;
	game->process->alive += op_tab[0].cycles;
	game->process->duration += op_tab[0].cycles;
	if (id > 0 && id < 5)
	{
		game->champ[id].alive += 1;
		ft_printf("Player %i (%s) is alive.", game->champ[id].nbr, game->champ[id].header.prog_name);
	}
	process->current =+ 4;
}