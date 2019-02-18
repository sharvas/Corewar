/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_in_buf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 13:20:54 by erli              #+#    #+#             */
/*   Updated: 2019/02/18 10:03:47 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <stdlib.h>

/*
** write nb_byte of arg in data->buf and update data->cursor.
** if buf is too small, malloc, then realloc it, setting data->mallocked
** as needed.
** return -1 if malloc fails, 1 otherwise.
*/

int			asm_malloc_buf(t_asm_data *data)
{
	char	*new;
	char	*str;

	str = "Warning, abort champ too big, rerun with -c to force\n";
	if (data->buf_size + B_SIZE > MAX_MALLOC_SIZE && (data->options & 1) == 0)
		return (ft_msg_int(1, str, -1));
	if ((data->mallocked & 4) == 0)
	{
		if (!(new = (char *)malloc(sizeof(char) * (data->buf_size + B_SIZE))))
			return (ft_msg_int(2, "failed malloc buff.\n", -1));
		new = ft_memcpy(new, data->buf, data->cursor);
		data->mallocked = (data->mallocked | 4);
		data->buf_size = data->buf_size + B_SIZE;
		data->buf = new;
	}
	else
	{
		if (!(new = (char *)realloc(data->buf,
						sizeof(char) * (data->buf_size + B_SIZE))))
			return (ft_msg_int(2, "failed realloc buff.\n", -1));
		data->buf = new;
		data->buf_size = data->buf_size + B_SIZE;
	}
	return (1);
}

int			asm_write_in_buf(t_asm_data *data, int arg, int nb_bytes)
{
	int				i;
	unsigned char	*str;

	i = 0;
	while (data->cursor + nb_bytes >= data->buf_size)
	{
		if (asm_malloc_buf(data) < 0)
			return (-1);
	}
	str = (unsigned char *)&arg;
	while (i < nb_bytes)
	{
		data->buf[data->cursor + nb_bytes - i - 1] = str[i];
		i++;
	}
	data->cursor = data->cursor + nb_bytes;
	return (1);
}
