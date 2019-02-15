/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:57:44 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/13 12:57:45 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void    print_dump(unsigned char *arena)
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
	//free everything?
	exit(1);
}

void	print_usage(/*t_game *game*/)
{
	ft_putstr("\nusage:\t./corewar [-dump nbr_cycles] ");
	ft_putstr("[[-n number] champion1.cor] ...\n\n");
	ft_putstr("\t[-dump nbr_cycles] at the end of nbr_cycles of executions, ");
	ft_putstr("dump the memory on the standard output and quit\n");
	ft_putstr("\t[-n number] sets the number of the next player\n");
	ft_putstr("\t[-v] vizualizer\n");
	ft_putstr("\t[-w nbr_cycles] wait for nbr_cycles before starting vizualizer\n");
	ft_putstr("\t[-cp] color process pointers according to which champion is the parent\n\n");
//	free_everything(/*t_game *game*/);
	exit(1);
}