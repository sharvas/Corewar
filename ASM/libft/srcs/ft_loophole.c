/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loophole.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:40:07 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 11:54:00 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_loophole(t_format *format, t_liststr **list, ...)
{
	va_list		ap;
	t_converter	fun;
	int			is_error;

	va_start(ap, list);
	is_error = 0;
	is_error = get_converter(format, &fun);
	if (is_error == -1)
	{
		free_format(format);
		return (lststr_dellall(list));
	}
	is_error = fun(format, ap, list);
	va_end(ap);
	return (is_error);
}
