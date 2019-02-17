/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:35:44 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/04 14:35:45 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_free_game(t_game *game)
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

void	error_exit(char *err_message, t_game *game)
{
	ft_putstr("ERROR ");
	ft_putstr(err_message);
	ft_putstr("\n");
	ft_free_game(game);
	exit (1);
}

void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(*game));
	ft_bzero(game->arena_champs, sizeof(MEM_SIZE));
	game->cycle_to_die = CYCLE_TO_DIE;
	game->cycle = CYCLE_TO_DIE;
}

int 	main(int argc, char **argv)
{
	t_game	game;

	init_game(&game);
	read_args(argc, argv, &game);
	if (game.flag_i)
		print_intro(&game);
	if (game.flag_v)
		ft_printf("%s", CLEAR);
	if (game.dump_set && !game.flag_dump)
		print_dump(game.arena, &game);
	else
		ft_game(&game);
	ft_free_game(&game);
	return (0);
}