/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 10:32:46 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 10:41:52 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		*ft_memalloc_c(size_t n, int c)
{
	void			*ptr;
	size_t			i;
	unsigned char	*str;

	if (!(ptr = malloc(n)))
		return (0);
	i = 0;
	str = (unsigned char *)ptr;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (ptr);
}
