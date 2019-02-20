/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 12:01:42 by erli              #+#    #+#             */
/*   Updated: 2018/11/09 11:30:39 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dstbyte;
	unsigned char	*srcbyte;
	int				i;

	dstbyte = (unsigned char *)dst;
	srcbyte = (unsigned char *)src;
	if (dst < src)
	{
		i = 0;
		while ((size_t)i < len)
		{
			dstbyte[i] = srcbyte[i];
			i++;
		}
	}
	else
	{
		i = len - 1;
		while (i >= 0)
		{
			dstbyte[i] = srcbyte[i];
			i--;
		}
	}
	return (dst);
}
