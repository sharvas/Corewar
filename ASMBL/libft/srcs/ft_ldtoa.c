/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:19:28 by erli              #+#    #+#             */
/*   Updated: 2018/12/12 14:16:22 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static	int		max_power(long double nb, long double *pow, int precision)
{
	int len;

	len = 1;
	if (nb < 0)
	{
		*pow = -1;
		len++;
	}
	if (nb == -2147483648)
	{
		*pow *= 10;
		len++;
	}
	while (nb / *pow >= 10)
	{
		*pow *= 10;
		len++;
	}
	if (precision == 0)
		return (len);
	else
		return (len + 1 + precision);
}

static	void	fill_decimals(long double nb, char *str, int i, int precision)
{
	int pow;

	if (precision != 0)
	{
		pow = (nb < 0 ? -10 : 10);
		str[i] = '.';
		i++;
		nb = nb - (int)nb;
		while (precision > 0)
		{
			str[i] = (int)(nb * pow) + 48;
			nb = (10 * nb) - (pow / 10) * (int)(str[i] - 48);
			i++;
			precision--;
		}
	}
	str[i] = '\0';
}

char			*ft_ldtoa(long double nb, int precision)
{
	long double	pow;
	int			i;
	int			len;
	char		*str;

	pow = 1;
	i = 0;
	len = max_power(nb, &pow, precision);
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		i++;
	}
	while (pow >= 1 || pow <= -1)
	{
		str[i] = (int)(nb / pow) + 48;
		nb = (nb - (str[i] - 48) * pow);
		pow /= 10;
		i++;
	}
	fill_decimals(nb, str, i, precision);
	return (str);
}
