/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_d_prt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 09:29:36 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 11:42:25 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		max_width(const t_format *format, int *tab, int len)
{
	int			width;
	long long	pow;
	int			i;
	int			max;

	i = 0;
	max = 0;
	while (i < len)
	{
		pow = 1;
		width = 0;
		while (tab[i] / pow != 0)
		{
			pow *= 10;
			width++;
		}
		if (width > max)
			max = width;
		i++;
	}
	return (format->m_width > max ? format->m_width : max);
}

static	int		make_list_tmp(t_format *format, int *tab, int len,
					t_liststr **list_tmp)
{
	t_format	*format_tab;
	t_format	*copy;
	int			i;

	i = 0;
	if (len < 0 || (copy_format(&format_tab, format) == -1))
	{
		free_format(format);
		return (lststr_dellall(list_tmp));
	}
	format_tab->pointer = 0;
	format_tab->m_width = max_width(format, tab, len);
	while (i < len)
	{
		copy_format(&copy, format_tab);
		if (ft_loophole(copy, list_tmp, tab[i]) == -1)
		{
			free_format(format);
			return (lststr_dellall(list_tmp));
		}
		i++;
	}
	free_format(format_tab);
	return (1);
}

static	int		add_in_list(t_liststr **list, t_liststr *bubble)
{
	char	*str;
	int		is_err;

	str = ft_strdup(bubble->content);
	is_err = lststr_addback(list, &str, bubble->len);
	if (is_err == -1)
		return (-1);
	str = ft_strdup(", ");
	if (str == NULL)
		return (-1);
	if (bubble->next == NULL)
	{
		str[0] = '}';
		str[1] = '\0';
	}
	is_err = lststr_addback(list, &str, ft_strlen(str));
	return (is_err);
}

static	int		add_list_tmp(t_liststr **list_tmp, t_liststr **list)
{
	char		*str;
	int			is_err;
	t_liststr	*bubble;

	if (!(str = ft_strdup("\n{")))
		return (lststr_dellall(list_tmp));
	is_err = lststr_addback(list, &str, ft_strlen(str));
	if (is_err == -1)
		return (lststr_dellall(list_tmp));
	bubble = *list_tmp;
	while (bubble != NULL && is_err != -1)
	{
		is_err = add_in_list(list, bubble);
		bubble = bubble->next;
	}
	if (is_err == -1)
		return (lststr_dellall(list_tmp));
	lststr_dellall(list_tmp);
	return (1);
}

int				ft_conv_d_ptrd(t_format *format, va_list ap, t_liststr **list)
{
	int			*nb_tab;
	int			len;
	t_liststr	*list_tmp;

	nb_tab = va_arg(ap, int*);
	len = va_arg(ap, int);
	list_tmp = NULL;
	if (make_list_tmp(format, nb_tab, len, &list_tmp) == -1)
		return (lststr_dellall(list));
	free_format(format);
	if (add_list_tmp(&list_tmp, list) == -1)
		return (lststr_dellall(list));
	return (1);
}
