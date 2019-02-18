/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:57:06 by erli              #+#    #+#             */
/*   Updated: 2018/11/07 12:13:02 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*data;
	size_t			i;

	data = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		data[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
