/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:48:16 by erli              #+#    #+#             */
/*   Updated: 2018/11/09 13:42:02 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *src)
{
	unsigned int		i;
	unsigned int		start;
	unsigned int		end;

	i = 0;
	start = 0;
	end = 0;
	if (src == NULL)
		return (NULL);
	while (src[i] == ' ' || src[i] == '\t' || src[i] == '\n')
		i++;
	start = i;
	end = i;
	while (src[i] != '\0')
	{
		while (src[i] != ' ' && src[i] != '\t' && src[i] != '\n'
			&& src[i] != '\0')
			i++;
		end = i;
		while ((src[i] == ' ' || src[i] == '\t' || src[i] == '\n')
			&& src[i] != '\0')
			i++;
	}
	return (ft_strsub(src, start, (size_t)(end - start)));
}
