/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_nbrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 18:33:01 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/17 18:33:02 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	read_dump_nbr(char *nbr, t_game *game)
{
	int			i;
	intmax_t	tmp;

	i = -1;
	while (nbr[++i])
		if (!ft_isdigit(nbr[i]))
			error_exit("argument following -d not a valid number", game);
	tmp = ft_atoi_intmax(nbr);
	if (tmp > 2147483647 || tmp < 0)
		error_exit("-dump number outside of acceptable range", game);
	game->flag_dump = ft_atoi(nbr);
	game->dump_set = 1;
}

void		read_dump(char **argv, t_game *game, int i)
{
	if (argv[i + 1])
		read_dump_nbr(argv[++i], game);
	else
		error_exit("no nbr_cycles argument after -dump", game);
}

void		read_speed(char *nbr, t_game *game)
{
	int	i;

	i = -1;
	while (nbr[++i])
		if (!ft_isdigit(nbr[i]))
			return ;
	game->speed = ft_atoi(nbr);
	if (game->speed < 1 || game->speed > 100)
		error_exit("-v number outside acceptable range (1-100)", game);
}

void		read_w_nbr(char *nbr, t_game *game)
{
	int			i;
	intmax_t	tmp;

	i = -1;
	while (nbr[++i])
		if (!ft_isdigit(nbr[i]))
			error_exit("argument following -w not a valid number", game);
	tmp = ft_atoi_intmax(nbr);
	if (tmp > 2147483647 || tmp < 0)
		error_exit("-w number outside of acceptable range", game);
	game->flag_w = tmp;
}

void		read_n_nbr(char *nbr, t_game *game, int champ_count)
{
	int			i;
	intmax_t	tmp;

	i = 0;
	if (!ft_isdigit(nbr[0]) && !(nbr[0] == '-') && !(nbr[0] == '+'))
		error_exit("-n number first digit invalid", game);
	while (nbr[++i])
		if (!ft_isdigit(nbr[i]))
			error_exit("-n number invalid", game);
	tmp = ft_atoi_intmax(nbr);
	if (tmp > 2147483647 || tmp < -2147483648)
		error_exit("-n number outside of acceptable range", game);
	game->champ[champ_count].nbr = tmp;
	game->champ[champ_count].nbr_set = 1;
	i = 0;
	while (++i < champ_count)
		if (game->champ[champ_count].nbr == game->champ[i].nbr)
			error_exit("-n number duplicate, try another number", game);
}
