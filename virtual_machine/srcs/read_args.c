/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 13:00:12 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/13 13:00:13 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			apply_mod(int champ_total, int champ_count)
{
	int	mod;

	mod = 0;
	if (champ_total % 2)
		mod = 1;
	if (MEM_SIZE % champ_total && champ_count > ((champ_total / 2) + mod))
		return (1);
	else
		return (0);
}

static int	find_champ_total(int argc, char **argv)
{
	int	champ_total;

	champ_total = 0;
	while (argc--)
	{
		if (ft_strstr(argv[argc], ".cor"))
			champ_total++;
		if (champ_total > MAX_PLAYERS)
			error_exit("too many champions", NULL);
	}
	return (champ_total);
}

static void	cut_names(t_game *game)
{
	int	champ;
	int	i;

	champ = 0;
	while (++champ <= game->champ_total)
	{
		i = 0;
		while (game->champ[champ].header.prog_name[i]
		&& game->champ[champ].header.prog_name[i] != '\n'
		&& game->champ[champ].header.prog_name[i] != '\t'
		&& i < 71)
			i++;
		ft_strncpy(game->champ[champ].name,
			game->champ[champ].header.prog_name, i);
	}
}

void		read_args(int argc, char **argv, t_game *game)
{
	int	i;
	int	champ_count;

	game->champ_total = find_champ_total(argc, argv);
	i = 1;
	champ_count = 1;
	if (argc == 1)
		print_usage(game);
	while (i < argc)
		i = read_arg(&champ_count, argv, game, i);
	if (game->flag_v)
	{
		game->flag_arg = 0;
		game->flag_op = 0;
		cut_names(game);
	}
}
