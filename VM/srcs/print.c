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

void    print_dump(unsigned char *arena, t_game *game)
{
	int	i;
	
	i = 0;
	ft_printf("%s%s%s", CLEAR, MOVE_CURSOR, HIDE_CURSOR);
	ft_printf("0x%.4x : ", i);
	while(i < MEM_SIZE)
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

void	print_visualizer(t_game *game, int i)
{
	short	champ_nbr;
	
	champ_nbr = 0;
	ft_printf("%s%s", MOVE_CURSOR, HIDE_CURSOR);
	print_arena_color(game);
	ft_printf("\n\tCycle delta: %2i\t\tNbr_live: %2i/%i\tChecks %.1i/%i\tCycle to die: %-4i\tCycles left in current period: %-4i\tCycle count: %i\n\n", CYCLE_DELTA, game->alive_count, NBR_LIVE, i, MAX_CHECKS, game->cycle_to_die, game->cycle, game->cycle_count);
	ft_printf("\tProcess count: %-21i\n\n", ft_count_process(game));
	ft_printf("\t%sPlayer %11i %-54s\tlives in current period: %s%-21d%s \tlast alive: %s%-21d\n", RED, game->champ[1].nbr, game->champ[1].header.prog_name, RESET, game->champ[1].alive_count, RED, RESET, game->champ[1].last_alive);
	if (game->champ_count >= 2)
		ft_printf("\t%sPlayer %11i %-54s\tlives in current period: %s%-21d%s \tlast alive: %s%-21d\n", GREEN, game->champ[2].nbr, game->champ[2].header.prog_name, RESET, game->champ[2].alive_count, GREEN, RESET, game->champ[2].last_alive);
	if (game->champ_count >= 3)
		ft_printf("\t%sPlayer %11i %-54s\tlives in current period: %s%-21d%s \tlast alive: %s%-21d\n", BLUE, game->champ[3].nbr, game->champ[3].header.prog_name, RESET, game->champ[3].alive_count, BLUE, RESET, game->champ[3].last_alive);
	if (game->champ_count >= 4)
		ft_printf("\t%sPlayer %11i %-54s\tlives in current period: %s%-21d%s \tlast alive: %s%-21d\n", YELLOW, game->champ[4].nbr, game->champ[4].header.prog_name, RESET, game->champ[4].alive_count, YELLOW, RESET, game->champ[4].last_alive);
	ft_printf("\n%s", RESET_CURSOR);
	if (game->speed)
		usleep(4200000 / game->speed);
}

void	print_usage(t_game *game)
{
	ft_putstr("\nusage:\t./corewar [-dump nbr_cycles] [-p] [-a] [-arg] [-w nbr_cycles] ");
	ft_putstr("[-v [speed (1-100)]] [-cp] [[-n number] champion1.cor] ...\n\n");
	ft_putstr("\t[-dump nbr_cycles] at the end of nbr_cycles of executions, ");
	ft_putstr("dump the memory on the standard output and quit\n");
	ft_putstr("\t[-a] don't print live operations\n");
	ft_putstr("\t[-op] print operations excecuted, for debugging\n");
	ft_putstr("\t[-arg] print argument sizes, for debugging\n");
	ft_putstr("\t[-i] print introduction of contestants\n");
	ft_putstr("\t[-n number] sets the number of the next player\n");
	ft_putstr("\t[-v [speed (1-100)]] vizualizer, optional speed ");
	ft_putstr("between 1 (slow) and 100 (fast)\n");
	ft_putstr("\t[-w nbr_cycles] wait for nbr_cycles before starting vizualizer\n");
	ft_putstr("\t[-cp] color process pointers according to which champion is the parent\n\n");
	ft_free_game(game);
	exit(1);
}

void	print_intro(t_game *game)
{
	int	champ;

	champ = 0;
	ft_printf("Introducing contestants...\n");
	while (++champ <= game->champ_count)
		ft_printf("Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", game->champ[champ].nbr, game->champ[champ].header.prog_size, game->champ[champ].header.prog_name, game->champ[champ].header.comment);
}