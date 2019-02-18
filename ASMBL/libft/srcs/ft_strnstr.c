/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:49:09 by erli              #+#    #+#             */
/*   Updated: 2018/11/09 10:09:44 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haysack, const char *needle, size_t n)
{
	size_t i;
	size_t j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haysack);
	while (haysack[i] != '\0' && i < n)
	{
		j = 0;
		while (haysack[i + j] == needle[j] && needle[j] != '\0'
			&& (i + j) < n)
			j++;
		if (needle[j] == '\0')
			return (((char *)haysack) + i);
		i++;
	}
	return (NULL);
}
