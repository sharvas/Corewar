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

	id = ft_reverse_bytes(&game->arena[(process->index + 1) % MEM_SIZE], DIR_SIZE);
	process->alive = 1;
	if (game->flag_op)
		ft_printf("LIVE(%i) number: %i\n", process->champ, id);
	if (id > 0 && id <= game->champ_count)
	{
		if (game->alive_count < 21)
			game->alive_count++;
		game->champ[id].alive_count++;
		game->champ[id].last_alive = game->cycle_count;
		if (!game->flag_v && !game->flag_a && !game->flag_op)
			ft_printf("A process shows that player %i (%s) is alive\n", game->champ[id].nbr, game->champ[id].header.prog_name);
	}
	process->index += DIR_SIZE;
}

void	op_zjmp(t_game *game, t_process *process)
{
	short	index;

	ft_get_index(&game->arena[(process->index + 1) % MEM_SIZE], IND_SIZE, &index);
	if (game->flag_op)
		ft_printf("ZJMP(%i) index: %i\n", process->champ, index);
	if (process->carry)
		process->index = ft_index_mod(process->index - 1 + index);
}

void	op_aff(t_game *game, t_process *process)
{
	t_arg_type		args[4];

	process->seek_index = process->index;
	find_args(&game->arena[++process->seek_index % MEM_SIZE], args);
	if (args[0] == REG_CODE
	&& game->arena[(process->seek_index + 1) % MEM_SIZE] >= 1
	&& game->arena[(process->seek_index + 1) % MEM_SIZE] <= REG_NUMBER)
	{
		if (game->flag_op)
			ft_printf("AFF(%i) %c", process->champ, process->reg[game->arena[++process->seek_index % MEM_SIZE]] % 256);//debug mode
		process->index = process->seek_index;
	}
}