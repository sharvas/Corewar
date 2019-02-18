/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 12:43:58 by erli              #+#    #+#             */
/*   Updated: 2019/02/14 19:47:07 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <unistd.h>

/*
** ecrit le contenut de header dans le fichier pointe par data->dest_fd
*/

static	void	asm_write_header2(t_asm_data *data, t_header *header)
{
	unsigned char	*ptr;
	int				i;

	ptr = (unsigned char *)&(header->prog_size);
	write(data->dest_fd, ptr + 3, 1);
	write(data->dest_fd, ptr + 2, 1);
	write(data->dest_fd, ptr + 1, 1);
	write(data->dest_fd, ptr, 1);
	ptr = (unsigned char *)header->comment;
	write(data->dest_fd, ptr, COMMENT_LENGTH + 1);
	i = 4 - ((COMMENT_LENGTH + 1) % 4);
	while (i > 0)
	{
		write(data->dest_fd, "\0", 1);
		i--;
	}
}

void			asm_write_header(t_asm_data *data, t_header *header)
{
	unsigned char	*ptr;
	int				i;

	if (data == 0 || header == 0)
		return ;
	ptr = (unsigned char *)&(header->magic);
	write(data->dest_fd, ptr + 3, 1);
	write(data->dest_fd, ptr + 2, 1);
	write(data->dest_fd, ptr + 1, 1);
	write(data->dest_fd, ptr, 1);
	ptr = (unsigned char *)header->prog_name;
	write(data->dest_fd, ptr, PROG_NAME_LENGTH + 1);
	i = 4 - ((PROG_NAME_LENGTH + 1) % 4);
	while (i > 0)
	{
		write(data->dest_fd, "\0", 1);
		i--;
	}
	asm_write_header2(data, header);
}
