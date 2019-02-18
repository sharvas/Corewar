/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:57:44 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/13 12:57:45 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_intro(t_game *game)
{
	int	champ;

	champ = 0;
	ft_printf("Introducing contestants...\n");
	while (++champ <= game->champ_total)
		ft_printf("Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		game->champ[champ].nbr,
		game->champ[champ].header.prog_size,
		game->champ[champ].header.prog_name,
		game->champ[champ].header.comment);
}

void		print_dump(unsigned char *arena, t_game *game)
{
	int	i;

	i = 0;
	ft_printf("%s%s", CLEAR, MOVE_CURSOR);
	ft_printf("0x%.4x : ", i);
	while (i < MEM_SIZE)
	{
		ft_printf("%.2x", (unsigned int)arena[i]);
		if (i == MEM_SIZE - 1)
			ft_printf("\n");
		else if (i && (i + 1) % 64 == 0)
			ft_printf("\n%#.4x : ", i + 1);
		else
			ft_printf(" ");
		i++;
	}
	ft_free_game(game);
	exit(1);
}

static void	print_arena_color(t_game *game)
{
	int			i;
	int			printed;

	i = 0;
	ft_printf("0x%.4x : ", i);
	while (i < MEM_SIZE)
	{
		printed = print_process(game, i);
		if (!printed && print_champ_condition(game, i))
		{
			print_champ(game, i);
			printed++;
		}
		if (!printed)
			ft_printf("%s%.2x%s", GREY, (unsigned int)game->arena[i], RESET);
		if (i == MEM_SIZE - 1)
			ft_printf("\n");
		else if (i && (i + 1) % 64 == 0)
			ft_printf("\n%#.4x : ", i + 1);
		else
			ft_printf(" ");
		i++;
	}
}

static void	print_v_champ(t_game *game)
{
	ft_printf("\t%sPlayer %11i %-54s\t\tlives in current period: %s%-21d%s\
	\tlast alive: %s%-21d\n", RED, game->champ[1].nbr,
	game->champ[1].header.prog_name, RESET, game->champ[1].alive_count,
	RED, RESET, game->champ[1].last_alive);
	if (game->champ_total >= 2)
		ft_printf("\t%sPlayer %11i %-54s\t\tlives in current period: %s%-21d%s\
		last alive: %s%-21d\n", GREEN, game->champ[2].nbr,
		game->champ[2].header.prog_name, RESET, game->champ[2].alive_count,
		GREEN, RESET, game->champ[2].last_alive);
	if (game->champ_total >= 3)
		ft_printf("\t%sPlayer %11i %-54s\t\tlives in current period: %s%-21d%s\
		last alive: %s%-21d\n", BLUE, game->champ[3].nbr,
		game->champ[3].header.prog_name, RESET, game->champ[3].alive_count,
		BLUE, RESET, game->champ[3].last_alive);
	if (game->champ_total >= 4)
		ft_printf("\t%sPlayer %11i %-54s\t\tlives in current period: %s%-21d%s\
		last alive: %s%-21d\n", YELLOW, game->champ[4].nbr,
		game->champ[4].header.prog_name, RESET, game->champ[4].alive_count,
		YELLOW, RESET, game->champ[4].last_alive);
}

void		print_visualizer(t_game *game, int i)
{
	short	champ_nbr;

	champ_nbr = 0;
	ft_printf("%s%s", MOVE_CURSOR, HIDE_CURSOR);
	print_arena_color(game);
	ft_printf("\n\tCycle delta: %2i\t", CYCLE_DELTA);
	ft_printf("\tNbr_live: %2i/%i", game->alive_count, NBR_LIVE);
	ft_printf("\t Checks: %2i/%i", i, MAX_CHECKS);
	ft_printf("\tCycle to die: %-4i", game->cycle_to_die);
	ft_printf("\tCycles left in current period: %-4i", game->cycle);
	ft_printf("\tCycle count: %i\n\n", game->cycle_count);
	ft_printf("\tProcess count: %-21i\n\n", count_process(game));
	print_v_champ(game);
	ft_printf("\n%s", RESET_CURSOR);
	if (game->speed)
		usleep(4200000 / game->speed);
}
