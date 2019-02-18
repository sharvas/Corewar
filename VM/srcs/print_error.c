/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 10:03:28 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/18 10:03:29 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_usage(t_game *game)
{
	ft_putstr("\nusage:\t./corewar [-dump nbr_cycles] [-i] [-a] [-op] [-arg]");
	ft_putstr(" [-v [speed (1-100)]] [-w nbr_cycles] [-cp] [-e]");
	ft_putstr(" [[-n number] champion1.cor] ...\n\n");
	ft_putstr("\t[-dump nbr_cycles] at the end of nbr_cycles of executions, ");
	ft_putstr("dump the memory on the standard output and quit\n");
	ft_putstr("\t[-i] print introduction of contestants\n");
	ft_putstr("\t[-a] don't print live operations\n");
	ft_putstr("\t[-op] print operations excecuted, for debugging\n");
	ft_putstr("\t[-arg] print argument sizes, for debugging\n");
	ft_putstr("\t[-v [speed (1-100)]] vizualizer, optional speed ");
	ft_putstr("between 1 (slow) and 100 (fast)\n");
	ft_putstr("\t[-w nbr_cycles] wait nbr_cycles before starting vizualizer\n");
	ft_putstr("\t[-cp] in visualizer color process pointers");
	ft_putstr(" according to which champion is the parent\n");
	ft_putstr("\t[-e] print \"Game ended at cycle count: (cycle_count)\"\n");
	ft_putstr("\t[-n number] sets the number of the next player\n\n");
	ft_free_game(game);
	exit(1);
}

void	error_exit(char *err_message, t_game *game)
{
	ft_putstr("ERROR ");
	ft_putstr(err_message);
	ft_putstr("\n");
	ft_free_game(game);
	exit(1);
}
