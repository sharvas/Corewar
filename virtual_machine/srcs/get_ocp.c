/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ocp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 16:43:25 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/20 19:13:30 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	find_args(t_game *game, int index, t_arg_type arg[4], int flag_arg)
{
	unsigned char	mask;

	mask = 192;
	arg[0] = (mask & game->arena[index % MEM_SIZE]) >> 6;
	arg[1] = ((mask >> 2) & game->arena[index % MEM_SIZE]) >> 4;
	arg[2] = ((mask >> 4) & game->arena[index % MEM_SIZE]) >> 2;
	arg[3] = (mask >> 6) & game->arena[index % MEM_SIZE];
	if (flag_arg)
	{
		ft_printf("arg1 - %i\n", arg[0]);
		ft_printf("arg2 - %i\n", arg[1]);
		ft_printf("arg3 - %i\n", arg[2]);
		ft_printf("arg4 - %i\n", arg[3]);
	}
}

void	get_size(unsigned int *size, t_arg_type args, int i)
{
	if (args == REG_CODE)
		*size = 1;
	else if (args == IND_CODE)
		*size = IND_SIZE;
	else if (args == DIR_CODE)
		*size = DIR_SIZE / i;
	else
		*size = 0;
}

int		reverse_bytes(void *ptr)
{
	int				ret_four;
	int				i;
	int				size;
	unsigned char	*n;

	ret_four = 0;
	i = 0;
	size = 4;
	n = (unsigned char *)&ret_four;
	while (size-- > 0)
	{
		*(n + size) = *((unsigned char *)ptr + i);
		i++;
	}
	return (ret_four);
}

int		read_bytes(t_game *game, int index, int size)
{
	short			ret_two;
	int				ret_four;
	int				i;
	unsigned char	*n;

	ret_two = 0;
	ret_four = 0;
	i = 0;
	if (size <= 2)
	{
		n = (unsigned char *)&ret_two;
		while (size-- > 0)
			*(n + size) = *(unsigned char *)(game->arena + ((index + i++)
				% MEM_SIZE));
		return (ret_two);
	}
	else if (size <= 4)
	{
		n = (unsigned char *)&ret_four;
		while (size-- > 0)
			*(n + size) = *(unsigned char *)(game->arena + ((index + i++)
				% MEM_SIZE));
		return (ret_four);
	}
	return (0);
}
