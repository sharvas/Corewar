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

static void	read_dump(char *nbr, t_game *game)
{
	int	i;

	i = -1;
	while (nbr[++i])
		if (!ft_isdigit(nbr[i]))
			error_exit("argument following -d not a valid number");
	game->flag_dump = ft_atoi(nbr);
	game->dump_set = 1;
}

static void	read_w(char *nbr, t_game *game)
{
	int	i;

	i = -1;
	while (nbr[++i])
		if (!ft_isdigit(nbr[i]))
			error_exit("argument following -w not a valid number");
	game->flag_w = ft_atoi(nbr);
	// ft_printf("flag_w: %d\n", game->flag_dump);//
}

static void	read_nbr(char *nbr, t_game *game, int champ_count)
{
	int	i;
	intmax_t	tmp;

	i = 0;
	if (!ft_isdigit(nbr[0]) && !(nbr[0] == '-') && !(nbr[0] == '+'))
		error_exit("-n number first digit invalid");
	while (nbr[++i])
		if (!ft_isdigit(nbr[i]))
			error_exit("-n number invalid");
	tmp = ft_atoi_intmax(nbr);
	if (tmp > 2147483647 || tmp < -2147483648)
		error_exit("-n number outside of acceptable range");
	game->champ[champ_count].nbr = tmp;
	i = 0;
	while (++i < champ_count)
		if (game->champ[champ_count].nbr == game->champ[i].nbr)
			error_exit("-n number duplicate, try another number");
	// ft_printf("champ->nbr: %d\n", game->champ[champ_count].nbr);
}

static void	read_speed(char *nbr, t_game *game)
{
	int	i;

	i = -1;
	while (nbr[++i])
		if (!ft_isdigit(nbr[i]))
			return ;
	game->speed = ft_atoi(nbr);
	if (game->speed < 1 || game->speed > 100)
		error_exit("argument following -v outside acceptable range (1-100)");
	// ft_printf("speed: %d\n", game->speed);//
}


void	    read_args(int argc, char **argv, t_game *game)
{
	int	i;
	unsigned char	champ_count;

	game->champ_count = find_champ_total(argc, argv);
	i = 1;
	champ_count = 1;
	if (argc == 1)
		print_usage();
	while (i < argc)
	{
		if (ft_strcmp((argv[i]), "-v") == 0)
		{
			game->flag_v = 1;
			if (argv[i + 1])
			{
				read_speed(argv[i + 1], game);
				if (game->speed)
					i++;
			}
		}
		else if (ft_strcmp((argv[i]), "-w") == 0)
		{
			if (argv[i + 1])
				read_w(argv[++i], game);
			else
				error_exit("no nbr_cycles argument after -w");
		}
		else if (ft_strcmp((argv[i]), "-cp") == 0)
			game->flag_cp = 1;
		else if (ft_strcmp((argv[i]), "-dump") == 0)
		{
			if (argv[i + 1])
				read_dump(argv[++i], game);
			else
				error_exit("no nbr_cycles argument after -dump");
		}
		else if (ft_strcmp((argv[i]), "-i") == 0)
			game->flag_i = 1;
		else if (ft_strcmp((argv[i]), "-n") == 0)
		{
			if (argv[i + 1])
			{
				game->champ[champ_count].nbr = 0;
				read_nbr(argv[++i], game, champ_count);
			}
			else
				error_exit("no champion number argument after -n");
			if (argv[i + 1] && ft_strstr(argv[i + 1], ".cor"))
				read_champion(argv[++i], game, champ_count++, game->champ_count);
			else
				error_exit("lacking valid .cor following -n [number]");
		}
		else if (ft_strstr(argv[i], ".cor"))
		{
			game->champ[champ_count].nbr = 0;
			read_champion(argv[i], game, champ_count++, game->champ_count);
		}
		else
			print_usage();
		i++;
	}
}