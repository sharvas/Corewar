/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_made_of_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 12:55:32 by erli              #+#    #+#             */
/*   Updated: 2019/01/09 13:46:23 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_made_of_str(char *str, char *base)
{
	int i;

	i = 0;
	if (str == 0 || base == 0)
		return (0);
	while (str[i] != '\0')
	{
		if (ft_char_in_str(str[i], base) == 0)
			return (0);
		i++;
	}
	return (1);
}
