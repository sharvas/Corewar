/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mat_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 14:18:11 by erli              #+#    #+#             */
/*   Updated: 2018/12/05 14:30:38 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free_mat_char(char **mat, int row)
{
	int i;

	i = 0;
	if (mat == NULL)
		return ;
	while (i < row)
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}
