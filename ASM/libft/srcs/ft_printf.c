/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:09:57 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 11:36:42 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		manage_dir(const char *format_str, int *i, va_list ap,
					t_liststr **list)
{
	t_format	*format;
	t_converter	fun;
	int			is_err;

	is_err = 0;
	format = NULL;
	is_err = init_format(&format);
	if (is_err == -1)
		return (-1);
	is_err = manage_format(format_str, &format, i, ap);
	if (is_err == -1)
	{
		free_format(format);
		return (-1);
	}
	is_err = get_converter(format, &fun);
	if (is_err == -1)
		return (-1);
	return (fun(format, ap, list));
}

static	int		read_format_str(const char *format_str, va_list ap,
					t_liststr **list)
{
	int		i;
	int		is_err;
	char	*str;
	int		j;

	i = 0;
	is_err = 0;
	while (format_str[i] != '\0' && is_err >= 0)
	{
		j = i;
		while (format_str[i] != '%' && format_str[i] != '\0' && is_err >= 0)
			i++;
		if (i > j)
		{
			if (!(str = ft_strsub_i_j((char *)format_str, j, i - 1))
				|| lststr_addback(list, &str, (i - j)) == -1)
				return (lststr_dellall(list));
		}
		if (format_str[i] == '%' && is_err >= 0)
		{
			i++;
			is_err = manage_dir(format_str, &i, ap, list);
		}
	}
	return (is_err == -1 ? -1 : 1);
}

int				ft_printf(const char *format_str, ...)
{
	va_list		ap;
	t_liststr	*list;
	int			is_err;

	va_start(ap, format_str);
	list = NULL;
	is_err = read_format_str(format_str, ap, &list);
	va_end(ap);
	if (is_err == -1)
		return (-1);
	return (lststr_unload(&list));
}
