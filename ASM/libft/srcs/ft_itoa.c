/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:19:28 by erli              #+#    #+#             */
/*   Updated: 2018/12/12 14:15:59 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static	int		max_power(int nb, int *pow)
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
	return (len);
}

char			*ft_itoa(int nb)
{
	int		pow;
	int		i;
	char	*str;

	pow = 1;
	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (max_power(nb, &pow) + 1))))
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		i++;
	}
	while (pow != 0)
	{
		str[i] = nb / pow + 48;
		nb = nb % pow;
		pow /= 10;
		i++;
	}
	str[i] = '\0';
	return (str);
}
