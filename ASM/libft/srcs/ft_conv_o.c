/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_o.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 09:29:36 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 11:48:00 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	char	*make_str(const t_format *format, unsigned long long nb,
					unsigned long long *pow, int *num_len)
{
	char	*str;
	int		str_len;

	*pow = 1;
	*num_len = 1;
	while (nb / *pow >= 8)
	{
		*pow *= 8;
		*num_len = *num_len + 1;
	}
	str_len = (format->precision > *num_len ? format->precision : *num_len);
	if (!(str = (char *)ft_memalloc_c(sizeof(char) * (str_len + 1), 32)))
		return (0);
	str[str_len] = '\0';
	return (str);
}

static	char	*ft_itoa_long_long(const t_format *format,
					unsigned long long nb)
{
	int					num_len;
	unsigned long long	pow;
	char				*str;
	int					i;
	int					str_len;

	if (!(str = make_str(format, nb, &pow, &num_len)))
		return (0);
	i = 0;
	str_len = ft_strlen(str);
	while (i < str_len - num_len)
	{
		str[i] = '0';
		i++;
	}
	while (pow != 0)
	{
		str[i] = nb / pow + '0';
		nb = nb % pow;
		pow /= 8;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static	char	*join_width(const t_format *format, char **str, char **str_add)
{
	char	*sign;

	sign = NULL;
	if (format->pound && (*str)[0] != '0' && (*str_add)[0] != '0')
		sign = "0";
	if ((*str_add)[0] == '0')
		*str = ft_strjoinfree(str_add, str, 3);
	else
	{
		if (!(*str = ft_strjoinfree(&sign, str, 2)))
			return (NULL);
		if (format->minus)
			*str = ft_strjoinfree(str, str_add, 3);
		else
			*str = ft_strjoinfree(str_add, str, 3);
	}
	return (*str);
}

static	char	*add_width(const t_format *format, char **str)
{
	char	*str_add;
	int		nb_spaces;
	int		i;

	if (*str == NULL)
		return (0);
	nb_spaces = format->m_width - ft_strlen(*str) - ((*str)[0] != '0'
		&& format->pound && !(format->zero));
	if (nb_spaces > 0)
		str_add = (char *)malloc(sizeof(char) * (nb_spaces + 1));
	else
		str_add = (char *)ft_memalloc_c(sizeof(char) * 1, 0);
	if (str_add == NULL)
		return (0);
	i = 0;
	while (i < nb_spaces)
	{
		str_add[i] = ((10 * format->precision + format->zero == -9)
			? '0' : ' ');
		i++;
	}
	str_add[i] = '\0';
	*str = join_width(format, str, &str_add);
	return (*str);
}

int				ft_conv_o(t_format *format, va_list ap, t_liststr **list)
{
	unsigned long long	nb;
	char				*str;

	if (!ft_strncmp(format->data_format_modifier, "l", 2))
		nb = (unsigned long long)va_arg(ap, long);
	else if (!ft_strncmp(format->data_format_modifier, "ll", 2))
		nb = (unsigned long long)va_arg(ap, long long);
	else if (!ft_strncmp(format->data_format_modifier, "h", 2))
		nb = (unsigned long long)(unsigned short)va_arg(ap, int);
	else if (!ft_strncmp(format->data_format_modifier, "hh", 2))
		nb = (unsigned long long)(unsigned char)va_arg(ap, int);
	else
		nb = (unsigned long long)va_arg(ap, unsigned int);
	if (nb == 0 && format->precision == 0)
		str = (char *)ft_memalloc_c(1, 0);
	else
		str = ft_itoa_long_long(format, nb);
	if (!(str = add_width(format, &str)))
	{
		free_format(format);
		return (lststr_dellall(list));
	}
	free_format(format);
	return (lststr_addback(list, &str, ft_strlen(str)));
}
