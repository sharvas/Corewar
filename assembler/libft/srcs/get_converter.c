/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_converter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:21:23 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 10:20:16 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_con_tab.h"

int		get_converter(t_format *format, t_converter *fun)
{
	int		i;
	t_conv	*g_tab;

	i = 0;
	if (format->pointer == 1)
		g_tab = g_conv_tab_ptr;
	else if (format->pointer == 2)
		g_tab = g_conv_tab_mat;
	else
		g_tab = g_conv_tab;
	while (g_tab[i].symbol != 0)
	{
		if (g_tab[i].symbol == format->conversion)
		{
			*fun = g_tab[i].converter;
			return (1);
		}
		i++;
	}
	*fun = g_tab[i].converter;
	return (1);
}
