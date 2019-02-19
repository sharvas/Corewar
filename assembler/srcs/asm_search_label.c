/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_search_label.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 15:07:55 by erli              #+#    #+#             */
/*   Updated: 2019/02/14 18:42:27 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

int			asm_search_label(t_asm_data *data, char *name)
{
	int i;

	i = 0;
	while (i < data->lab_curs)
	{
		if (ft_strcmp(name, data->labels[i].name) == 0)
			return (i);
		i++;
	}
	return (-1);
}
