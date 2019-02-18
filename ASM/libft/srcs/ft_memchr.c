/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:19:25 by erli              #+#    #+#             */
/*   Updated: 2018/11/09 10:21:34 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	byte;
	unsigned char	*str;
	size_t			i;

	i = 0;
	byte = (unsigned char)c;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == byte)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
