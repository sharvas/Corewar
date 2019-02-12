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

void    print_arena_color(t_game *game)
{
	int			i;
	int			printed;
	t_process	*process;
	char 		color[12] = "\033[47;1;31m"; // define in .h with all other codes
	char 		color1[12] = "\033[0;34m";
	char		color0[6] = "\033[0m";

	i = 0;
	ft_printf("0x%.4x : ", i);
	while(i < MEM_SIZE)
	{
		printed = 0;
		process = game->process;
		while (process)
		{
			if (i == process->index)
			{
				ft_printf("%s%.2x%s", color, (unsigned int)game->arena[i], color0);
				printed++;
			}
			if (printed == game->champ_count)
				break ;
			process = process->next;
		}
		if (!printed)
			ft_printf("%s%.2x%s", color1, (unsigned int)game->arena[i], color0);
		if (i == MEM_SIZE - 1)
			ft_printf("\n");
		else if (i && (i + 1) % 64 == 0)
			ft_printf("\n%#.4x : ", i + 1);
		else
			ft_printf(" ");
		i++;
	}
}

void    print_arena(unsigned char *arena)
{
	int	i;
	
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

void	error_exit(char *err_message)
{
	ft_putstr("ERROR ");
	ft_putstr(err_message);
	ft_putstr("\n");
	//free everything
	exit (1);
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
	// ft_printf("champ->nbr: %d\n", game->champ[champ_count].nbr);
}

// void	fill_memory(t_game *game, int index, int champ)
// {
// 	while 
// } //set champ no where it belongs and then print in color

void	read_champion(char *cor, t_game *game, int champ_count, int champ_total)
{
	int				fd;
	unsigned char	binary[FILE_SIZE + 1];
	int				i;
	size_t			weight;

	i = 0;
	ft_bzero(binary, sizeof(binary));
	if ((fd = open(cor, O_RDONLY)) < 0)
		print_usage();//replace with error message
	weight = read(fd, binary, FILE_SIZE + 1);//integrate
	if (weight > FILE_SIZE)
		error_exit("champion size too big");
	if (weight < (PROG_NAME_LENGTH + COMMENT_LENGTH + 4))
		error_exit("champion size too small");
	ft_printf("weight: %u\n", weight);
	close(fd);
	if (!game->champ[champ_count].nbr)
		game->champ[champ_count].nbr = champ_count;
	ft_printf("nbr: %d\n", game->champ[champ_count].nbr);//
	ft_memcpy(&game->champ[champ_count].header.magic, (binary + 1), 3);
	ft_printf("magic: %x\n", (unsigned int)ft_reverse_bytes((unsigned char *)&game->champ[champ_count].header.magic, 3));
	ft_strncat(game->champ[champ_count].header.prog_name, (char*)(binary + 4), PROG_NAME_LENGTH);
	ft_printf("name: %s\n", game->champ[champ_count].header.prog_name);//
	ft_strncat(game->champ[champ_count].header.comment, (char*)(binary + 4 + 136), COMMENT_LENGTH);
	ft_printf("comment: %s\n\n", game->champ[champ_count].header.comment);//
	ft_printf("champ_total: %d, champ_count: %d, index: %d\n", champ_total, champ_count, (MEM_SIZE / champ_total) * (champ_count));//
	ft_memcpy(game->arena + ((MEM_SIZE / champ_total) * (champ_count)), (binary + 144 + COMMENT_LENGTH), CHAMP_MAX_SIZE - 16);//whats this number all about??
	game->champ[champ_count].start_index = (MEM_SIZE / champ_total) * (champ_count);
	// fill_memory(game, (MEM_SIZE / champ_total) * (champ_count), champ_count);
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
	if (champ_total > 4)
		error_exit("too many champions");
	return (champ_total);
}

void	read_args(int argc, char **argv, t_game *game)
{
	int	i;
	int	champ_count;

	game->champ_count = find_champ_total(argc, argv);
	ft_printf("champ_total: %d\n", game->champ_count);
	i = 1;
	champ_count = 0;
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

void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(*game));
	game->cycle_to_die = CYCLE_TO_DIE;
	game->cycle = CYCLE_TO_DIE;
	game->frame_rate = 1;
}

int main(int argc, char **argv)
{
	t_game	game;

	init_game(&game);
	read_args(argc, argv, &game);
	ft_printf("\033[2J");
	print_arena(game.arena);
	usleep(500000);
	ft_printf("\033[2J");
	ft_game(&game);
	// if (game.dump)//change to deal with cycles
	//	print_arena(game.arena);
	return (0);
}