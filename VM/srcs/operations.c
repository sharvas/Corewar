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

int		*find_args(unsigned char *ptr)
{
	unsigned char	mask;
	int				arg[4];

	mask = 192;
	arg[0] = (mask & *ptr) >> 6;
	ft_printf("arg - %u\n", arg[0]);
	arg[1] = ((mask >> 2) & *ptr) >> 4;
	ft_printf("arg - %u\n", arg[1]);
	arg[2] = ((mask >> 4) & *ptr) >> 2;
	ft_printf("arg - %u\n", arg[2]);
	arg[3] = (mask >> 6) & *ptr;
	ft_printf("arg - %u\n", arg[3]);
	return (arg);
}

void	op_ld(t_game *game, t_process *process)
{
	int		id;
	t_op	*op_tab;
	int		*args;

	op_tab = ft_get_op();
	args = find_args(&process->current[(process->index + 1) % MEM_SIZE]);
	id = ft_reverse_bytes(&process->current[(process->index + 1) % MEM_SIZE], sizeof(id));
	process->alive++;
	process->duration += op_tab[0].cycles;
	if (id >= 0 && id <= game->champ_count)
	{
		game->alive += 1;
		ft_printf("Player %i (%s) is alive!\n", game->champ[id].nbr, game->champ[id].header.prog_name);
		process->index += 4;
	}
}

void	op_sti(t_game *game, t_process *process)
{
	
}