/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 10:41:06 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/18 10:41:07 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	read_v(char **argv, t_game *game, int i)
{
	game->flag_v = 1;
	if (argv[i + 1])
	{
		read_speed(argv[i + 1], game);
		if (game->speed)
			i++;
	}
	return (i);
}

static void	read_w(char **argv, t_game *game, int i)
{
	if (argv[i + 1])
		read_w_nbr(argv[++i], game);
	else
		error_exit("no nbr_cycles argument after -w", game);
}

static int	read_n(char **argv, t_game *game, int i, int champ_count)
{
	if (argv[i + 1])
	{
		game->champ[champ_count].nbr = 0;
		read_n_nbr(argv[++i], game, champ_count);
	}
	else
		error_exit("no champion number argument after -n", game);
	if (argv[i + 1] && ft_strstr(argv[i + 1], ".cor"))
		read_champion(argv[++i], game, champ_count, game->champ_total);
	else
		error_exit("lacking valid .cor following -n [number]", game);
	return (i);
}

int			read_arg(int *champ_count, char **argv, t_game *game, int i)
{
	if (ft_strcmp((argv[i]), "-dump") == 0)
		read_dump(argv, game, i++);
	else if (ft_strcmp((argv[i]), "-i") == 0)
		game->flag_i = 1;
	else if (ft_strcmp((argv[i]), "-a") == 0)
		game->flag_a = 1;
	else if (ft_strcmp((argv[i]), "-op") == 0)
		game->flag_op = 1;
	else if (ft_strcmp((argv[i]), "-arg") == 0)
		game->flag_arg = 1;
	else if (ft_strcmp((argv[i]), "-v") == 0)
		i = read_v(argv, game, i);
	else if (ft_strcmp((argv[i]), "-w") == 0)
		read_w(argv, game, i++);
	else if (ft_strcmp((argv[i]), "-cp") == 0)
		game->flag_cp = 1;
	else if (ft_strcmp((argv[i]), "-e") == 0)
		game->flag_e = 1;
	else if (ft_strcmp((argv[i]), "-n") == 0)
		i = read_n(argv, game, i, (*champ_count)++);
	else if (ft_strstr(argv[i], ".cor"))
		read_champion(argv[i], game, (*champ_count)++, game->champ_total);
	else
		print_usage(game);
	return (++i);
}
