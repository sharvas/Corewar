/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:11:24 by erli              #+#    #+#             */
/*   Updated: 2018/11/15 10:20:26 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t l_dest;
	size_t l_src;
	size_t j;

	l_dest = 0;
	l_src = 0;
	j = 0;
	while (dst[l_dest] != '\0')
		l_dest++;
	while (src[l_src] != '\0')
		l_src++;
	if (l_dest > n)
		return (l_src + n);
	while (src[j] != '\0' && (l_dest + j) < (n - 1))
	{
		dst[l_dest + j] = src[j];
		j++;
	}
	dst[l_dest + j] = '\0';
	return (l_dest + l_src);
}
