/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ocp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 16:43:25 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/17 16:43:30 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	find_args(unsigned char *ptr, t_arg_type arg[], int flag_arg)
{
	unsigned char	mask;

	mask = 192;
	arg[0] = (mask & *ptr) >> 6;
	arg[1] = ((mask >> 2) & *ptr) >> 4;
	arg[2] = ((mask >> 4) & *ptr) >> 2;
	arg[3] = (mask >> 6) & *ptr;
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

int		reverse_bytes(void *ptr, unsigned int size)
{
	short		ret_two;
	int			ret_four;
	int			i;

	ret_two = 0;
	ret_four = 0;
	i = 0;
	if (size <= 2)
	{
		while (size-- > 0)
			ret_two |= *((unsigned char *)ptr + i++) << (size * 8);
		return (ret_two);
	}
	else if (size <= 4)
	{
		while (size-- > 0)
			ret_four |= *((unsigned char *)ptr + i++) << (size * 8);
		return (ret_four);
	}
	return (0);
}
