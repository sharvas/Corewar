/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lload.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 18:46:02 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/17 18:46:03 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	op_lld_ind(t_game *game, t_process *process, short *index,
int *value)
{
	*index = reverse_bytes(&game->arena[++process->seek % MEM_SIZE],
		IND_SIZE);
	*value = reverse_bytes(&game->arena[index_mod(process->seek
		- 2 + *index) % MEM_SIZE], IND_SIZE);
	process->reg[game->arena[(process->seek + IND_SIZE)
		% MEM_SIZE]] = *value;
	if (game->flag_op)
		ft_printf("LLD(%i) value: %i, reg: %i\n", process->champ, *value,
		game->arena[(process->seek + IND_SIZE) % MEM_SIZE]);
	process->seek += IND_SIZE;
	process->carry = 1;
	process->index = process->seek;
}

void		op_lld(t_game *game, t_process *process)
{
	int			value;
	short		index;
	t_arg_type	args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args, game->flag_arg);
	if (args[0] == DIR_CODE && args[1] == REG_CODE
	&& check_args(game, process->seek, args, 13))
	{
		value = reverse_bytes(&game->arena[++process->seek % MEM_SIZE],
			DIR_SIZE);
		process->reg[game->arena[(process->seek + DIR_SIZE)
			% MEM_SIZE]] = value;
		if (game->flag_op)
			ft_printf("LLD(%i) value: %i, reg: %i\n", process->champ, value,
			game->arena[(process->seek + DIR_SIZE) % MEM_SIZE]);
		process->seek += DIR_SIZE;
		process->carry = 1;
		process->index = process->seek;
	}
	else if (args[0] == IND_CODE && args[1] == REG_CODE
	&& check_args(game, process->seek, args, 13))
		op_lld_ind(game, process, &index, &value);
	else
		process->index = move_index(process->index, args, 13);
}

static void	op_lldi_print_carry(t_game *game, t_process *process, int *value)
{
	if (game->flag_op)
		ft_printf("LLDI(%i) index: %i, reg: %i\n", process->champ,
		value[0] + value[1], game->arena[(process->seek - 1) % MEM_SIZE]);
	if (value[0] + value[1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	process->index = process->seek;
}

void		op_lldi(t_game *game, t_process *process)
{
	unsigned int	size[2];
	int				value[2];
	int				total_value;
	t_arg_type		args[4];

	process->seek = process->index;
	find_args(&game->arena[++process->seek % MEM_SIZE], args, game->flag_arg);
	get_size(&size[0], args[0], 2);
	get_size(&size[1], args[1], 2);
	if (args[0] && (args[1] == DIR_CODE || args[1] == REG_CODE)
	&& args[2] == REG_CODE
	&& check_args(game, process->seek, args, 14))
	{
		get_first_value_ind(game, process, args[0], &value[0]);
		get_second_value_ind(game, process, args[1], &value[1]);
		total_value = reverse_bytes(&game->arena[index_mod(process->seek - 1
			- size[0] - size[1] + value[0] + value[1]) % MEM_SIZE], REG_SIZE);
		process->reg[game->arena[++process->seek % MEM_SIZE]] = total_value;
		op_lldi_print_carry(game, process, value);
	}
	else
		process->index = move_index(process->index, args, 14);
}
