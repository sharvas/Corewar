/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:57:55 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/13 12:57:56 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	print_champ_condition(t_game *game, int i)
{
	int	j;

	j = 1;
	while (j < 5 && j <= game->champ_count)
	{
		if (game->arena_champs[i] == game->champ[j].nbr)
			return (1);
		j++;
	}
	return (0);
}

static void	print_process(t_game *game, int i)
{
	if (game->arena_champs[i] == game->champ[1].nbr)
		ft_printf("%s%.2x%s", BRED, (unsigned int)game->arena[i], RESET);
	else if (game->arena_champs[i] == game->champ[2].nbr && game->champ_count > 1)
		ft_printf("%s%.2x%s", BGREEN, (unsigned int)game->arena[i], RESET);
	else if (game->arena_champs[i] == game->champ[3].nbr && game->champ_count > 2)
		ft_printf("%s%.2x%s", BBLUE, (unsigned int)game->arena[i], RESET);
	else if (game->arena_champs[i] == game->champ[4].nbr && game->champ_count > 3)
		ft_printf("%s%.2x%s", BYELLOW, (unsigned int)game->arena[i], RESET);
	else
		ft_printf("%s%.2x%s", LIGHT, (unsigned int)game->arena[i], RESET);
}

static void	print_process_cp(t_game *game, int i, t_process *process)
{
	if (process->champ == game->champ[1].nbr)
		ft_printf("%s%.2x%s", BRED, (unsigned int)game->arena[i], RESET);
	else if (process->champ == game->champ[2].nbr)
		ft_printf("%s%.2x%s", BGREEN, (unsigned int)game->arena[i], RESET);
	else if (process->champ == game->champ[3].nbr)
		ft_printf("%s%.2x%s", BBLUE, (unsigned int)game->arena[i], RESET);
	else if (process->champ == game->champ[4].nbr)
		ft_printf("%s%.2x%s", BYELLOW, (unsigned int)game->arena[i], RESET);
}

static void	print_champ(t_game *game, int i)
{
	if (game->arena_champs[i] == game->champ[1].nbr)
		ft_printf("%s%.2x%s", RED, (unsigned int)game->arena[i], RESET);
	else if (game->arena_champs[i] == game->champ[2].nbr)
		ft_printf("%s%.2x%s", GREEN, (unsigned int)game->arena[i], RESET);
	else if (game->arena_champs[i] == game->champ[3].nbr)
		ft_printf("%s%.2x%s", BLUE, (unsigned int)game->arena[i], RESET);
	else if (game->arena_champs[i] == game->champ[4].nbr)
		ft_printf("%s%.2x%s", YELLOW, (unsigned int)game->arena[i], RESET);
}

void        print_arena_color(t_game *game)
{
	int			i;
	int			printed;
	t_process	*process;

	i = 0;
	ft_printf("0x%.4x : ", i);
	while(i < MEM_SIZE)
	{
		printed = 0;
		process = game->process;
		while (process)
		{
			if (i == process->index)
			{
				if (!game->flag_cp)
					print_process(game, i);
				else
					print_process_cp(game, i, process);
				printed++;
				break;
			}
			process = process->next;
		}
		if (!printed && print_champ_condition(game, i))
		{
			print_champ(game, i);
			printed++;
		}
		if (!printed)
			ft_printf("%.2x", (unsigned int)game->arena[i]);
		if (i == MEM_SIZE - 1)
			ft_printf("\n");
		else if (i && (i + 1) % 64 == 0)
			ft_printf("\n%#.4x : ", i + 1);
		else
			ft_printf(" ");
		i++;
	}
}
