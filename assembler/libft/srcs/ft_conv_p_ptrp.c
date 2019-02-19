/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_d_prt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 09:29:36 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 11:51:49 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		make_list_tmp(t_format *format, unsigned long *tab, int len,
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
	format_tab->m_width = (format->m_width > 10 ? format->m_width : 10);
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

int				ft_conv_p_ptrp(t_format *format, va_list ap, t_liststr **list)
{
	unsigned long	*nb_tab;
	int				len;
	t_liststr		*list_tmp;

	nb_tab = va_arg(ap, unsigned long*);
	len = va_arg(ap, int);
	list_tmp = NULL;
	if (make_list_tmp(format, nb_tab, len, &list_tmp) == -1)
		return (lststr_dellall(list));
	free_format(format);
	if (add_list_tmp(&list_tmp, list) == -1)
		return (lststr_dellall(list));
	return (1);
}
