/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 09:02:50 by erli              #+#    #+#             */
/*   Updated: 2018/11/09 13:05:27 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*ft_memalloc(size_t n)
{
	void			*memzone;
	char			*s;
	size_t			i;

	if (!(memzone = malloc(n)))
		return (NULL);
	s = (char *)memzone;
	i = 0;
	while (i < n)
	{
		s[i] = 0;
		i++;
	}
	return (memzone);
}
