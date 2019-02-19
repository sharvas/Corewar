/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:33:18 by erli              #+#    #+#             */
/*   Updated: 2018/11/07 17:15:49 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *str, int a)
{
	char	c;
	int		i;
	int		i_last;

	c = (char)a;
	i = 0;
	i_last = -1;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i_last = i;
		i++;
	}
	if (a == 0)
		return (((char *)str + i));
	if (i_last < 0)
		return (NULL);
	return (((char *)str + i_last));
}
