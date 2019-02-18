/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:05:33 by erli              #+#    #+#             */
/*   Updated: 2018/11/15 10:19:16 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	void			*next;
	size_t			i;
	unsigned char	stop;
	unsigned char	*destbyte;
	unsigned char	*srcbyte;

	next = NULL;
	destbyte = (unsigned char *)dst;
	srcbyte = (unsigned char *)src;
	stop = (unsigned char)c;
	i = 0;
	while (i < n && srcbyte[i] != stop)
	{
		destbyte[i] = srcbyte[i];
		i++;
	}
	if (i < n)
	{
		destbyte[i] = srcbyte[i];
		next = (void *)(destbyte + i + 1);
	}
	return (next);
}
