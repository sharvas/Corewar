/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:12:58 by erli              #+#    #+#             */
/*   Updated: 2019/02/20 17:37:46 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			write_int(t_game *game, short address, int content)
{
	int				i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)(&content);
	while (i < 4)
	{
		game->arena[(address + i) % MEM_SIZE] = ptr[i];
		i++;
	}
}
