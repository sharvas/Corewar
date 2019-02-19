/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:49:09 by erli              #+#    #+#             */
/*   Updated: 2018/11/07 17:10:09 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haysack, const char *needle)
{
	size_t i;
	size_t j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haysack);
	while (haysack[i] != '\0')
	{
		j = 0;
		while (haysack[i + j] == needle[j] && needle[j] != '\0')
			j++;
		if (needle[j] == '\0')
			return (((char *)haysack) + i);
		i++;
	}
	return (NULL);
}
