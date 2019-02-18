/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:34:17 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 10:12:00 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int			write_free(int fd, char **str, size_t n)
{
	int ret;

	ret = write(fd, *str, n);
	free(*str);
	return (ret);
}

char		*ft_strsub_i_j(char *str, size_t begin, size_t end)
{
	char	*sub;
	size_t	i;
	int		len;

	if (end < begin)
		return (NULL);
	len = end - begin + 1;
	if (!(sub = (char *)ft_memalloc_c(sizeof(char) * (len + 1), 0)))
		return (NULL);
	i = begin;
	while (i <= end && str[i] != '\0')
	{
		sub[i - begin] = str[i];
		i++;
	}
	return (sub);
}

void		ft_round_up(char **str, int rest, char c, int i)
{
	char	*add;
	int		done;

	done = 0;
	add = "1";
	if (rest >= 5)
	{
		while (done == 0 && i >= 0)
		{
			if ((*str)[i] == '9')
				((*str)[i] = '0');
			else if ((*str)[i] >= '0' && (*str)[i] <= '8')
			{
				(*str)[i]++;
				done = 1;
			}
			i--;
		}
		if ((*str)[0] == '0' && c == 'f' && done == 0)
			*str = ft_strjoinfree(&add, str, 2);
		else if ((*str)[0] == '0' && c == 'e' && done == 0)
			ft_round_up_slide(str);
	}
}

void		ft_round_up_slide(char **str)
{
	int		i;

	ft_round_up(str, 6, 'f', ft_strlen(*str) - 1);
	i = ft_strlen(*str) - 5;
	while (i > 0)
	{
		(*str)[i] = (*str)[i - 1];
		i--;
	}
	(*str)[0] = '1';
}
