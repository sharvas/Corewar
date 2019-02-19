/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 09:42:55 by erli              #+#    #+#             */
/*   Updated: 2019/02/18 11:49:38 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>
#include <unistd.h>

/*
** free asm_data
*/

static	void	asm_free_names(t_label *lab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (lab[i].state == 1)
			free(lab[i].name);
		i++;
	}
}

void			asm_free_data(t_asm_data *data)
{
	if (data == 0)
		return ;
	if (data->dest_fd != -2)
		close(data->dest_fd);
	asm_free_names(data->labels, data->lab_curs);
	asm_free_names(data->holes, data->hol_curs);
	if ((data->mallocked & 1) == 1)
		free(data->labels);
	if ((data->mallocked & 2) == 2)
		free(data->holes);
	if ((data->mallocked & 4) == 4)
		free(data->buf);
}
