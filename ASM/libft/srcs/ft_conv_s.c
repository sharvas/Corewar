/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 09:29:36 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 11:52:24 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*add_width(t_format *format, char **str_arg)
{
	int		nb_spaces;
	int		len;
	char	*str;
	int		i;

	nb_spaces = format->m_width - ft_strlen(*str_arg);
	len = (nb_spaces < 0 ? 0 : nb_spaces);
	if (!(str = (char *)ft_memalloc_c(sizeof(unsigned char) * (len + 1), 0)))
		return (NULL);
	i = 0;
	while (i < nb_spaces)
	{
		str[i] = (format->zero ? '0' : ' ');
		i++;
	}
	if (format->minus)
		str = ft_strjoinfree(str_arg, &str, 3);
	else
		str = ft_strjoinfree(&str, str_arg, 3);
	return (str);
}

int				ft_conv_s(t_format *format, va_list ap, t_liststr **list)
{
	char	*str;
	char	*str_arg;

	str_arg = va_arg(ap, char*);
	if (str_arg == NULL)
	{
		if (!(str_arg = ft_strsub_i_j("(null)", 0, 5)))
			return (lststr_dellall(list));
	}
	else if (format->precision > 0)
		str_arg = ft_strsub_i_j(str_arg, 0, format->precision - 1);
	else if (format->precision == 0)
		str_arg = (char *)ft_memalloc_c(1, 0);
	else
		str_arg = ft_strsub_i_j(str_arg, 0, ft_strlen(str_arg));
	if (!(str = add_width(format, &str_arg)))
	{
		free_format(format);
		return (lststr_dellall(list));
	}
	free_format(format);
	return (lststr_addback(list, &str, ft_strlen(str)));
}
