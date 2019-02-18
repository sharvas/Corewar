/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 09:34:52 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 15:00:08 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoinfree(char **s1, char **s2, int n)
{
	char	*str;

	if (!(str = ft_strjoin(*s1, *s2)))
	{
		if (n == 1 || n == 3)
			free(*s1);
		if (n == 2 || n == 3)
			free(*s2);
		return (NULL);
	}
	if ((n == 1 || n == 3))
		free(*s1);
	if ((n == 2 || n == 3))
		free(*s2);
	return (str);
}
