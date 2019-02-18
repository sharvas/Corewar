/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 10:46:14 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/18 10:46:17 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(*game));
	ft_bzero(game->arena_champs, sizeof(MEM_SIZE));
	game->cycle_to_die = CYCLE_TO_DIE;
	game->cycle = CYCLE_TO_DIE;
}

void		ft_free_game(t_game *game)
{
	t_process *tmp;

	while (game && game->process)
	{
		tmp = game->process;
		game->process = game->process->next;
		free(tmp);
		tmp = NULL;
	}
}

int			main(int argc, char **argv)
{
	t_game	game;

	init_game(&game);
	read_args(argc, argv, &game);
	run_game(&game);
	ft_free_game(&game);
	return (0);
}
