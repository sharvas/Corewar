/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:53:43 by dfinnis           #+#    #+#             */
/*   Updated: 2019/02/13 11:53:44 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	find_args(unsigned char *ptr, t_arg_type arg[])
{
	unsigned char	mask;

	mask = 192;
	arg[0] = (mask & *ptr) >> 6;
	arg[1] = ((mask >> 2) & *ptr) >> 4;
	arg[2] = ((mask >> 4) & *ptr) >> 2;
	arg[3] = (mask >> 6) & *ptr;
}

void	ft_get_size(unsigned int *size, t_arg_type args, int i)
{
	if (args == REG_CODE)
		*size = T_REG;
	else if (args == IND_CODE)
		*size = IND_SIZE;
	else if (args == DIR_CODE)
		*size = DIR_SIZE / i;
	else
		*size = 0;
}