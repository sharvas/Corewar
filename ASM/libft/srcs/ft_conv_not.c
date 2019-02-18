/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 09:29:36 by erli              #+#    #+#             */
/*   Updated: 2019/01/21 13:34:18 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*add_width(t_format *format, char c, int *len)
{
	int		nb_spaces;
	int		i;
	char	*str;

	nb_spaces = format->m_width - 1;
	*len = (nb_spaces < 0 ? 0 : nb_spaces);
	if (!(str = (char *)ft_memalloc_c(sizeof(char) * (*len + 2), 32)))
		return (NULL);
	i = 0;
	if (format->minus)
	{
		str[0] = c;
		i++;
	}
	else
		str[*len] = c;
	while (i < nb_spaces)
	{
		str[i] = (format->zero ? '0' : ' ');
		i++;
	}
	str[*len + 1] = '\0';
	return (str);
}

int				ft_conv_not(t_format *format, va_list ap, t_liststr **list)
{
	char	*str;
	char	c;
	int		len;

	if (ap != NULL)
		c = '\0';
	c = format->conversion;
	str = add_width(format, c, &len);
	if (str == NULL)
	{
		free_format(format);
		return (lststr_dellall(list));
	}
	free_format(format);
	return (lststr_addback(list, &str, ft_strlen(str)));
}
