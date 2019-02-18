/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 09:33:20 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 13:08:55 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		test_format(t_format *format)
{
	if (format->zero && format->minus)
		format->zero = 0;
	if (format->plus && format->space)
		format->space = 0;
	return (1);
}

static	void	get_flags(const char *format_str, t_format *format, int *i)
{
	while (ft_char_in_str(format_str[*i], "mt#0+- "))
	{
		if (format_str[*i] == '#')
			format->pound = 1;
		if (format_str[*i] == '+')
			format->plus = 1;
		if (format_str[*i] == '-')
			format->minus = 1;
		if (format_str[*i] == '0')
			format->zero = 1;
		if (format_str[*i] == ' ')
			format->space = 1;
		if (format_str[*i] == 't')
			format->pointer = 1;
		if (format_str[*i] == 'm')
			format->pointer = 2;
		*i = *i + 1;
	}
}

static	int		ft_simple_atoi(t_format *format, const char *format_str,
					int *i, va_list ap)
{
	int nb;
	int j;

	j = *i;
	nb = 0;
	if (format_str[*i] == '*')
	{
		*i = *i + 1;
		nb = va_arg(ap, int);
		if (nb < 0 && format_str[j - 1] != '.')
		{
			nb = -nb;
			format->minus = 1;
		}
		else if (nb < 0)
			nb = -1;
	}
	if (format_str[*i] >= '0' && format_str[*i] <= '9' && *i)
		nb = 0;
	while (format_str[*i] >= '0' && format_str[*i] <= '9' && *i)
		nb = (10 * nb) + (format_str[(*i)++] - '0');
	if (j == *i && (format_str[j - 1] != '.' || format_str[j] == '.'))
		return (format->m_width);
	return (nb);
}

static	void	get_len_modifier(const char *format_str, t_format **format,
					int *i)
{
	if (ft_char_in_str(format_str[*i], LEGAL_MOD))
	{
		(*format)->data_format_modifier[0] = format_str[*i];
		if (format_str[*i] == format_str[*i + 1] && (format_str[*i] == 'h'
			|| format_str[*i] == 'l'))
		{
			(*format)->data_format_modifier[1] = format_str[*i];
			*i = *i + 1;
		}
		*i = *i + 1;
	}
}

int				manage_format(const char *format_str, t_format **format, int *i,
					va_list ap)
{
	int len;
	int no_prec;

	no_prec = 1;
	while (ft_char_in_str(format_str[*i], "#mt0123456789-+ *.jzlhL"))
	{
		get_flags(format_str, *format, i);
		len = ft_simple_atoi(*format, format_str, i, ap);
		(*format)->m_width = len;
		if (format_str[*i] == '.')
		{
			*i = *i + 1;
			no_prec = 0;
			len = ft_simple_atoi(*format, format_str, i, ap);
			(*format)->precision = (no_prec ? -1 : len);
		}
		get_flags(format_str, *format, i);
		get_len_modifier(format_str, format, i);
	}
	if (ft_char_in_str(format_str[*i], LEGAL_CONV))
		(*format)->conversion = format_str[(*i)++];
	else
		(*format)->conversion = (format_str[*i] == '\0' ? '\0'
			: format_str[(*i)++]);
	return (test_format(*format));
}
