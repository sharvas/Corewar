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

void	read_champion(char *cor, t_game *game, int champ_count, int champ_total)
{
	int		fd;
	unsigned char	binary[FILE_SIZE + 1];
	int		i;
	size_t	weight;

	i = 0;
	ft_bzero(binary, sizeof(binary));
	// if (!(binary = (char *)malloc(sizeof(char) * ((MEM_SIZE / 6) + 1 ))))
	// 	print_usage();//replace with error message
	if ((fd = open(cor, O_RDONLY)) < 0)
		print_usage();//replace with error message
	// if (get_next_line(fd, &binary) != 1)
	// 	print_usage();//replace with error message
	weight = read(fd, binary, FILE_SIZE + 1);//integrate
	if (weight > FILE_SIZE)
		ft_putstr("ERROR champion too fat\n");
	ft_printf("weight: %u\n", weight);
	close(fd);
	ft_memcpy(&game->champ[champ_count].header.magic, (char*)(binary + 1), 3);
	ft_printf("magic: %x\n", game->champ[champ_count].header.magic);//
	ft_strncat(game->champ[champ_count].header.prog_name, (char*)(binary + 4), PROG_NAME_LENGTH);
	ft_printf("name: %s\n", game->champ[champ_count].header.prog_name);//
	ft_strncat(game->champ[champ_count].header.comment, (char*)(binary + 4 + 136), COMMENT_LENGTH);
	ft_printf("comment: %s\n", game->champ[champ_count].header.comment);//
	ft_memcpy(game->arena + ((MEM_SIZE / champ_total) * (champ_count - 1)), (binary + 144 + COMMENT_LENGTH), CHAMP_MAX_SIZE - 16);//whats this number all about??
}

int		find_champ_total(int argc, char **argv)
{
	int	champ_total;

	champ_total = 0;
	while (argc--)
	{
		if (ft_strstr(argv[argc], ".cor"))
			champ_total++;
	}
	return (champ_total);
}

void	read_args(int argc, char **argv, t_game *game)
{
	int	i;
	int	champ_count;
	int	champ_total;

	champ_total = find_champ_total(argc, argv);
	ft_printf("champ_total: %d\n", champ_total);
	i = 1;
	champ_count = 1;
	if (argc == 1)
		print_usage();
	while (i < argc)
	{
		if (ft_strcmp((argv[i]), "-dump") == 0)
		{
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
			if (argv[i + 1] && ft_strstr(argv[i + 1], ".cor"))
				read_champion(argv[++i], game, champ_count++, champ_total);
			else
				print_usage();
		}
		else if (ft_strstr(argv[i], ".cor"))
			read_champion(argv[i], game, champ_count++, champ_total);
		else
			print_usage();
		i++;
	}
}

int main(int argc, char **argv)
{
	t_game			game;

	ft_bzero(&game, sizeof(game));
	read_args(argc, argv, &game);
	// if (game.dump)//change to deal with cycles
		print_arena(game.arena);
	return (0);
}