/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live_jmp_aff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 11:02:40 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/18 11:02:43 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	op_live(t_game *game, t_process *process)
{
	int		id;

	id = reverse_bytes(&game->arena[(process->index + 1) % MEM_SIZE],
		DIR_SIZE);
	process->alive = 1;
	if (game->flag_op)
		ft_printf("LIVE(%i) number: %i\n", process->champ, id);
	if (id > 0 && id <= game->champ_total)
	{
		if (game->alive_count < 21)
			game->alive_count++;
		game->champ[id].alive_count++;
		game->champ[id].last_alive = game->cycle_count;
		if (!game->flag_v && !game->flag_a && !game->flag_op)
			ft_printf("A process shows that player %i (%s) is alive\n",
			game->champ[id].nbr, game->champ[id].header.prog_name);
	}
	process->index += DIR_SIZE;
}

void	op_zjmp(t_game *game, t_process *process)
{
	short	index;

	get_index(&game->arena[(process->index + 1) % MEM_SIZE],
		IND_SIZE, &index);
	if (game->flag_op)
		ft_printf("ZJMP(%i) index: %i, carry: %i\n", process->champ,
		index, process->carry);
	if (process->carry)
		process->index = index_mod(process->index - 1 + index);
	else
		process->index += DIR_SIZE / 2;
}

void	op_aff(t_game *game, t_process *process)
{
	t_arg_type		args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args, game->flag_arg);
	if (args[0] == REG_CODE
	&& check_args(game, process->seek, args, 16))
	{
		if (game->flag_op)
			ft_printf("AFF(%i) %c\n", process->champ,
			process->reg[game->arena[++process->seek % MEM_SIZE]] % 256);
		ft_printf("%c", process->reg[game->arena[++process->seek
			% MEM_SIZE]] % 256);
		process->index = process->seek;
	}
	else
		process->index = move_index(process->index, args, 16);
}
