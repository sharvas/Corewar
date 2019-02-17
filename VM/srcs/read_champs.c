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

void	read_champion(char *cor, t_game *game, unsigned char champ_count, int champ_total)
{
	int				fd;
	unsigned char	binary[FILE_SIZE + 1];
	unsigned int	i;
	int				j;
	unsigned int	champ_tmp;
	int				weight;

	i = 0;
	j = 0;
	champ_tmp = champ_count;
	ft_bzero(binary, sizeof(binary));

	if ((fd = open(cor, O_RDONLY)) < 0)
		error_exit("failed to open .cor file");
	weight = read(fd, binary, FILE_SIZE + 1);
	if (weight == -1)
		error_exit("read .cor failed");
	if (weight > FILE_SIZE)
		error_exit("champion size too big");
	if (weight < (PROG_NAME_LENGTH + COMMENT_LENGTH + 4))
		error_exit("champion size too small");
	close(fd);

	if (!game->champ[champ_count].nbr_set)
	{
		while (++j < champ_count)
			if (champ_tmp == game->champ[j].nbr)
				champ_tmp++;
		game->champ[champ_count].nbr = champ_tmp;
	}

	ft_memcpy(&game->champ[champ_count].header.magic, (binary + 1), 3);
	game->champ[champ_count].header.magic = ft_reverse_bytes((unsigned char *)&game->champ[champ_count].header.magic, 3);
	if (game->champ[champ_count].header.magic != COREWAR_EXEC_MAGIC)
		error_exit("champion magic number doesn't match COREWAR_EXEC_MAGIC");

	ft_strncat(game->champ[champ_count].header.prog_name, (char*)(binary + 4), PROG_NAME_LENGTH);

	ft_memcpy(&game->champ[champ_count].header.prog_size, (binary + 138), 2);
	game->champ[champ_count].header.prog_size = ft_reverse_bytes((unsigned char *)&game->champ[champ_count].header.prog_size, 2);
	if (game->champ[champ_count].header.prog_size != (unsigned int)(weight - PROG_NAME_LENGTH - COMMENT_LENGTH - 16))
		error_exit("prog_size doesn't match read size");

	ft_strncat(game->champ[champ_count].header.comment, (char*)(binary + 4 + 136), COMMENT_LENGTH);
	ft_memcpy(game->arena + ((MEM_SIZE / champ_total) * (champ_count - 1)), (binary + 144 + COMMENT_LENGTH), CHAMP_MAX_SIZE - 16);//whats this number all about??
	game->champ[champ_count].start_index = (MEM_SIZE / champ_total) * (champ_count - 1);
	while (i < game->champ[champ_count].header.prog_size)
		ft_memcpy(game->arena_champs + ((MEM_SIZE / champ_total) * (champ_count - 1)) + i++, &champ_count, 1);
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
