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

#include "../op.h"
#include <stdio.h>// change to ft_printf in libft
#include <string.h>//change to libft

void    print_arena(unsigned char *arena)
{
	int i;
	
	i = 0;
	printf("0x%.4x : ", i);
	while(i < MEM_SIZE)
	{
		printf("%.2x ", (unsigned int)arena[i]);
		if (i == MEM_SIZE - 1)
		{
			printf("\n");
			break ;
		}
		if (i && (i + 1) % 64 == 0)
			printf("\n%#.4x : ", i + 1);
		i++;
	}
}

int main(int argc, char **argv)
{
	argc = 0;//
	argv = NULL;//

	unsigned char   arena[MEM_SIZE];
	bzero(arena, MEM_SIZE);//ft_
	arena[20] = 'a';//ft_
	print_arena(arena);
	return (0);
}
