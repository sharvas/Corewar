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
			print_usage();
	game->dump = ft_atoi(nbr);
	ft_printf("dump: %d\n", game->dump);//
}

static void	read_nbr(char *nbr, t_game *game, int champ_count)
{
	int	i;

	i = -1;
	while (nbr[++i])
		if (!ft_isdigit(nbr[i]))
			print_usage();
	game->champ[champ_count].nbr = ft_atoi(nbr);
	i = 0;
	while (++i < champ_count)
		if (game->champ[champ_count].nbr == game->champ[i].nbr)
			error_exit("-n number duplicate, try another number");
	// ft_printf("champ->nbr: %d\n", game->champ[champ_count].nbr);
}

void	    read_args(int argc, char **argv, t_game *game)
{
	int	i;
	unsigned char	champ_count;

	game->champ_count = find_champ_total(argc, argv);
	ft_printf("champ_total: %d\n", game->champ_count);
	i = 1;
	champ_count = 1;
	if (argc == 1)
		print_usage();
	while (i < argc)
	{
		if (ft_strcmp((argv[i]), "-v") == 0)
			game->flag_v = 1;
		else if (ft_strcmp((argv[i]), "-cp") == 0)
			game->flag_cp = 1;
		else if (ft_strcmp((argv[i]), "-dump") == 0)
		{
			if (argv[i + 1])
				read_dump(argv[++i], game);
			else
				print_usage();
		}
		else if (ft_strcmp((argv[i]), "-n") == 0)
		{
			if (argv[i + 1])
			{
				game->champ[champ_count].nbr = 0;
				read_nbr(argv[++i], game, champ_count);
			}
			else
				print_usage();
			if (argv[i + 1] && ft_strstr(argv[i + 1], ".cor"))
				read_champion(argv[++i], game, champ_count++, game->champ_count);
			else
				print_usage();
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