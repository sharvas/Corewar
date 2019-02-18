/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_e.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 11:28:08 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 11:39:13 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	char	*make_str(const t_format *format, long double nb,
					long double *pow, int *expo)
{
	char	*str;
	int		str_len;

	*pow = 1;
	*expo = 0;
	if (nb < 0)
		*pow = -1;
	if (nb < -10 && (*expo)++ == 0)
		*pow = -10;
	while ((*pow * nb < 1 || nb / *pow >= 10) && nb != 0)
	{
		*pow *= 10;
		expo++;
	}
	str_len = 5;
	if (format->precision == -1)
		str_len += 7;
	else if (format->precision > 0)
		str_len += format->precision + 1;
	if (!(str = (char *)ft_memalloc_c(sizeof(char) * (str_len + 1), 32)))
		return (0);
	str[str_len] = '\0';
	if (nb < 1 && nb > -1)
		*expo *= -1;
	return (str);
}

static	char	*ft_itoa_e(const t_format *format, long double nb)
{
	long double	pow;
	int			expo;
	int			i;
	char		*str;

	if (!(str = make_str(format, nb, &pow, &expo)))
		return (NULL);
	nb = (expo < 0 ? nb * pow : nb / pow);
	str[0] = (int)(nb) + '0';
	i = 1;
	if (format->precision != 0)
		str[i++] = '.';
	while ((format->precision > 0 && i < format->precision + 2)
		|| (format->precision == -1 && i < 8))
	{
		nb = 10 * (nb - (int)nb);
		str[i++] = (int)nb + '0';
	}
	str[i++] = 'E';
	str[i++] = (expo < 0 ? '-' : '+');
	str[i] = ((expo * (44 - str[i - 1])) > 9 ? (expo / 10) + '0' : '0');
	i++;
	str[i] = (expo * (44 - str[i - 2])) % 10 + '0';
	ft_round_up(&str, 10 * (nb - (int)nb), 'e', ft_strlen(str) - 5);
	return (str);
}

static	char	*join_width(const t_format *format, char **str, char **str_add,
					long double nb)
{
	char *sign;

	sign = NULL;
	if (nb < 0)
		sign = "-";
	else if (format->plus)
		sign = "+";
	else if (format->space)
		sign = " ";
	if ((*str_add)[0] == '0')
	{
		if (!(*str_add = ft_strjoinfree(&sign, str_add, 2)))
			return (NULL);
		*str = ft_strjoinfree(str_add, str, 3);
	}
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

static	char	*add_width(const t_format *format, char **str, long double nb)
{
	char	*str_add;
	int		nb_spaces;
	int		i;

	if (*str == NULL)
		return (NULL);
	nb_spaces = format->m_width - (ft_strlen(*str)
		+ (nb < 0 || format->space || format->plus));
	if (nb_spaces > 0)
		str_add = (char *)malloc(sizeof(char) * (nb_spaces + 1));
	else
		str_add = (char *)ft_memalloc_c(1, 0);
	if (str_add == NULL)
		return (NULL);
	i = 0;
	while (i < nb_spaces)
	{
		str_add[i] = (format->zero == 1 ? '0' : ' ');
		i++;
	}
	str_add[i] = '\0';
	*str = join_width(format, str, &str_add, nb);
	return (*str);
}

int				ft_conv_big_e(t_format *format, va_list ap, t_liststr **list)
{
	long double	nb;
	char		*str;

	if (!ft_strncmp(format->data_format_modifier, "L", 2))
		nb = va_arg(ap, long double);
	else
		nb = (long double)va_arg(ap, double);
	str = ft_itoa_e(format, nb);
	if (!(str = add_width(format, &str, nb)))
	{
		free_format(format);
		return (lststr_dellall(list));
	}
	free_format(format);
	return (lststr_addback(list, &str, ft_strlen(str)));
}
