/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstrsplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:59:08 by erli              #+#    #+#             */
/*   Updated: 2018/11/08 14:17:47 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printstrsplit(char **split)
{
	int i;

	i = 0;
	while (split[i] != 0)
	{
		ft_putchar('\'');
		ft_putstr(split[i]);
		ft_putchar('\'');
		ft_putchar('\n');
		i++;
	}
}
