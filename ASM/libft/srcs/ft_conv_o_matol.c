/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_d_prt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 09:29:36 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 11:49:42 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		make_list_tmp(t_format *format, unsigned long **tab, int *dim,
					t_liststr **list_tmp)
{
	t_format	*format_tab;
	t_format	*copy;
	int			i;

	i = 0;
	if (dim[0] < 0 || (copy_format(&format_tab, format) == -1))
	{
		free_format(format);
		return (lststr_dellall(list_tmp));
	}
	format_tab->pointer = 1;
	while (i < dim[0])
	{
		copy_format(&copy, format_tab);
		if (ft_loophole(copy, list_tmp, tab[i], dim[1]) == -1)
		{
			free_format(format);
			return (lststr_dellall(list_tmp));
		}
		i++;
	}
	free_format(format_tab);
	return (1);
}

static	int		add_list_tmp(t_liststr **list_tmp, t_liststr **list)
{
	int			is_err;
	t_liststr	*bubble;
	char		*str;

	bubble = *list_tmp;
	while (bubble != NULL && is_err != -1)
	{
		str = ft_strdup(bubble->content);
		is_err = lststr_addback(list, &str, bubble->len);
		if (is_err == -1)
			return (-1);
		bubble = bubble->next;
	}
	if (is_err == -1)
		return (lststr_dellall(list_tmp));
	lststr_dellall(list_tmp);
	return (1);
}

int				ft_conv_o_matol(t_format *format, va_list ap, t_liststr **list)
{
	unsigned long	**nb_tab;
	int				dim[2];
	t_liststr		*list_tmp;

	nb_tab = va_arg(ap, unsigned long **);
	dim[0] = va_arg(ap, int);
	dim[1] = va_arg(ap, int);
	list_tmp = NULL;
	if (make_list_tmp(format, nb_tab, dim, &list_tmp) == -1)
		return (lststr_dellall(list));
	free_format(format);
	if (add_list_tmp(&list_tmp, list) == -1)
		return (lststr_dellall(list));
	return (1);
}
