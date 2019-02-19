/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 13:01:12 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/13 13:01:13 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	check_weight(int weight, t_game *game, int fd)
{
	if (weight == -1)
		error_exit("read .cor failed", game);
	if (weight > (int)FILE_SIZE)
		error_exit("champion size too big", game);
	if (weight < ((int)sizeof(struct s_header) + 2))
		error_exit("champion size too small", game);
	close(fd);
}

static void	read_champ_nbr(t_game *game, int champ_count)
{
	int	j;
	int	champ_tmp;

	j = 0;
	champ_tmp = champ_count;
	if (!game->champ[champ_count].nbr_set)
	{
		while (++j < champ_count)
			if (champ_tmp == game->champ[j].nbr)
				champ_tmp++;
		game->champ[champ_count].nbr = champ_tmp;
	}
}

static void	read_magic(t_game *game, int champ_count)
{
	game->champ[champ_count].header.magic =
		reverse_bytes((unsigned char *)&game->champ[champ_count].header.magic,
			4);
	if (game->champ[champ_count].header.magic != (unsigned int)
		COREWAR_EXEC_MAGIC)
		error_exit("champion magic number doesn't match COREWAR_EXEC_MAGIC",
			game);
}

static void	read_prog_size(t_game *game, int champ_count, int weight)
{
	game->champ[champ_count].header.prog_size =
		reverse_bytes((unsigned char *)
			&game->champ[champ_count].header.prog_size, 4);
	if (game->champ[champ_count].header.prog_size !=
		(unsigned int)(weight - sizeof(struct s_header)))
		error_exit("prog_size doesn't match read size", game);
}

void		read_champion(char *cor, t_game *game, int champ_count,
int champ_total)
{
	int				fd;
	unsigned char	binary[FILE_SIZE + 1];
	unsigned int	i;
	int				weight;

	i = 0;
	ft_bzero(binary, sizeof(binary));
	if ((fd = open(cor, O_RDONLY)) < 0)
		error_exit("failed to open .cor file", game);
	weight = read(fd, binary, FILE_SIZE + 1);
	check_weight(weight, game, fd);
	read_champ_nbr(game, champ_count);
	game->champ[champ_count].header = *(struct s_header *)binary;
	read_magic(game, champ_count);
	read_prog_size(game, champ_count, weight);
	ft_memcpy(game->arena + ((MEM_SIZE / champ_total) * (champ_count - 1)),
		(binary + sizeof(struct s_header)),
		game->champ[champ_count].header.prog_size);
	game->champ[champ_count].start_index = (MEM_SIZE / champ_total)
		* (champ_count - 1);
	while (i < game->champ[champ_count].header.prog_size)
		ft_memcpy(game->arena_champs + ((MEM_SIZE / champ_total)
		* (champ_count - 1)) + i++, &champ_count, 1);
}
