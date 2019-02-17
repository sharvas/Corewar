
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

static void	read_w_nbr(char *nbr, t_game *game)
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

static void	read_n_nbr(char *nbr, t_game *game, int champ_count)
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

static void	read_speed(char *nbr, t_game *game)
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

static void	read_dump(char **argv, t_game *game, int i)
{
	if (argv[i + 1])
		read_dump_nbr(argv[++i], game);
	else
		error_exit("no nbr_cycles argument after -dump", game);
}

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

static int	read_n(char **argv, t_game *game, int i, short champ_count)
{
	if (argv[i + 1])
	{
		game->champ[champ_count].nbr = 0;
		read_n_nbr(argv[++i], game, champ_count);
	}
	else
		error_exit("no champion number argument after -n", game);
	if (argv[i + 1] && ft_strstr(argv[i + 1], ".cor"))
		read_champion(argv[++i], game, champ_count++, game->champ_total);
	else
		error_exit("lacking valid .cor following -n [number]", game);
	return (i);
}

// static int	read_arg(int champ_count, char **argv, t_game *game, int i)
// {
// 	if (ft_strcmp((argv[i]), "-dump") == 0)
// 		read_dump(argv, game, i++);
// 	else if (ft_strcmp((argv[i]), "-i") == 0)
// 		game->flag_i = 1;
// 	else if (ft_strcmp((argv[i]), "-a") == 0)
// 		game->flag_a = 1;
// 	else if (ft_strcmp((argv[i]), "-op") == 0)
// 		game->flag_op = 1;
// 	else if (ft_strcmp((argv[i]), "-arg") == 0)
// 		game->flag_arg = 1;
// 	else if (ft_strcmp((argv[i]), "-v") == 0)
// 		i = read_v(argv, game, i);
// 	else if (ft_strcmp((argv[i]), "-w") == 0)
// 		read_w(argv, game, i++);
// 	else if (ft_strcmp((argv[i]), "-cp") == 0)
// 		game->flag_cp = 1;
// 	else if (ft_strcmp((argv[i]), "-e") == 0)
// 		game->flag_e = 1;
// 	else if (ft_strcmp((argv[i]), "-n") == 0)
// 		i = read_n(argv, game, i, champ_count++);
// 	else if (ft_strstr(argv[i], ".cor"))
// 		read_champion(argv[i], game, champ_count++, game->champ_total);
// 	else
// 		print_usage(game);
// 	return (++i);
// }

void		read_args(int argc, char **argv, t_game *game)
{
	int		i;
	short	champ_count;

	game->champ_total = find_champ_total(argc, argv);
	i = 1;
	champ_count = 1;
	while (champ_count <= game->champ_total)
		game->champ[champ_count++].nbr = 0;
	champ_count = 1;
	if (argc == 1)
		print_usage(game);
	while (i < argc)
	//	i = read_arg(champ_count, argv, game, i);
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
			i = read_n(argv, game, i, champ_count++);
		else if (ft_strstr(argv[i], ".cor"))
			read_champion(argv[i], game, champ_count++, game->champ_total);
		else
			print_usage(game);
	}
}
