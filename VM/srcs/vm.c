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

void    print_arena(unsigned char *arena)
{
	int i;
	
	i = 0;
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
}

void	print_usage(/*t_game *game*/)
{
	ft_putstr("\nusage:\t./corewar [-dump nbr_cycles] ");
	ft_putstr("[[-n number] champion1.cor] ...\n\n");
	ft_putstr("\t[-dump nbr_cycles] at the end of nbr_cycles of executions, ");
	ft_putstr("dump the memory on the standard output and quit\n");
	ft_putstr("\t[-n number] sets the number of the next player\n\n");
//	free_everything(/*t_game *game*/);
	exit(1);
}

void	read_dump(char *nbr, t_game *game)
{
	int	i;

	i = -1;
	while (nbr[++i])
		if (!ft_isdigit(nbr[i]))
			print_usage();
	game->dump = ft_atoi(nbr);//correct atoi?
	ft_printf("dump: %d\n", game->dump);//
}

void	read_nbr(char *nbr, t_game *game, int champ_count)
{
	int	i;

	i = -1;
	while (nbr[++i])
		if (!ft_isdigit(nbr[i]))
			print_usage();
	game->champ[champ_count].nbr = ft_atoi(nbr);//correct atoi?
	ft_printf("champ->nbr: %d\n", game->champ[champ_count].nbr);
}

// void	read_champion(t_game *game, char *cor, int champ_count)
// {

// }

void	read_args(int argc, char **argv, t_game *game)
{
	int	i;
	int	champ_count;

	i = 1;
	champ_count = 1;
	if (argc == 1)
		print_usage();
	while (i < argc)
	{
		// ft_printf("here\n");//
		if (ft_strcmp((argv[i]), "-dump") == 0)
		{
			// ft_printf("here_dump\n");//
			if (argv[i + 1])
				read_dump(argv[++i], game);
			else
				print_usage();
		}
		else if (ft_strcmp((argv[i]), "-n") == 0)
		{
			if (argv[i + 1])
				read_nbr(argv[++i], game, champ_count);
			else
				print_usage();
			// if (argv[i + 1] && ft_strstr(argv[i + 1], ".cor"))
			// 	read_champion(game, argv[++i], champ_count++);
			// else
			// 	print_usage();
		}
		// else if (ft_strstr(argv[i], ".cor"))
		// {
		// 	read_champion(game, argv[i], champ_count);
		// 	champ_count++;
		// }
		else
			print_usage();
		i++;
	}
}

int main(int argc, char **argv)
{
	t_game			game;
	unsigned char   arena[MEM_SIZE];

	ft_bzero(&game, sizeof(game));
	ft_bzero(arena, MEM_SIZE);
	read_args(argc, argv, &game);
	if (game.dump)//change to deal with cycles
		print_arena(arena);
	return (0);
}