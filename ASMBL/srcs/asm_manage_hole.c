/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_manage_hole.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 13:56:02 by erli              #+#    #+#             */
/*   Updated: 2019/02/18 10:06:48 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <stdlib.h>

/*
** Attempts to fill hole by going through data->labels.
** if successfull, applies modulo 65536 if half size, and applies IDX_MOD
** then calls write_to buf;
** Otherwise, create a hole pointing to data->cursor. If data->holes too small,
** malloc, then realloc it, setting data->malloced as needed.
** Return -1 if malloc fails.
*/

static	void	asm_init_holes(t_asm_data *data)
{
	int i;

	i = data->hol_curs;
	while (i < data->hol_curs)
	{
		data->holes[i].state = 0;
		i++;
	}
}

static	void	asm_holes_cpy(t_asm_data *data, t_label *new)
{
	int i;

	i = 0;
	while (i < data->hol_curs)
	{
		new[i].name = data->holes[i].name;
		new[i].size = data->holes[i].size;
		new[i].buf_position = data->holes[i].buf_position;
		new[i].instruction_curs = data->holes[i].instruction_curs;
		new[i].nb_byte = data->holes[i].nb_byte;
		new[i].opcode = data->holes[i].opcode;
		new[i].col = data->holes[i].col;
		new[i].state = data->holes[i].state;
		i++;
	}
}

static	int		asm_malloc_holes(t_asm_data *data)
{
	t_label *new;

	new = NULL;
	if ((data->holes_size + B_SIZE / 2) > MAX_MALLOC_SIZE)
		return (ft_msg_int(2, "Failed, holes_size too big.\n", -1));
	if ((data->mallocked & 2) == 2)
	{
		if (!(new = (t_label *)realloc(data->holes, sizeof(t_label)
			* (data->holes_size + B_SIZE / 2))))
			return (ft_msg_int(2, "Failed realloc for Holes.\n", -1));
		data->holes = new;
		data->holes_size = data->holes_size + B_SIZE / 2;
	}
	else
	{
		if (!(new = (t_label *)malloc(sizeof(t_label) * B_SIZE)))
			return (ft_msg_int(2, "Failed malloc holes.\n", -1));
		data->mallocked = (data->mallocked | 2);
		data->holes_size = B_SIZE;
		asm_holes_cpy(data, new);
		data->holes = new;
		asm_init_holes(data);
	}
	return (1);
}

static	int		asm_create_hole(t_asm_data *data, char *name, int nb_byte,
					int opcode)
{
	if (data->hol_curs >= data->holes_size)
	{
		if (asm_malloc_holes(data) < 0)
			return (-1);
	}
	if (!(data->holes[data->hol_curs].name = ft_strdup(name)))
		return (ft_msg_int(2, "Failed malloc for holes.name.\n", -1));
	data->holes[data->hol_curs].size = ft_strlen(name);
	data->holes[data->hol_curs].buf_position = data->cursor;
	data->holes[data->hol_curs].instruction_curs = data->instruction_cursor;
	data->holes[data->hol_curs].nb_byte = nb_byte;
	data->holes[data->hol_curs].opcode = opcode;
	data->holes[data->hol_curs].line = data->line;
	data->holes[data->hol_curs].col = data->col;
	data->holes[data->hol_curs].state = 1;
	data->hol_curs++;
	data->cursor += nb_byte;
	return (1);
}

int				asm_manage_hole(t_asm_data *data, char *arg, int nb_byte,
					int opcode)
{
	int lab_index;
	int	content;

	if ((lab_index = asm_search_label(data, arg)) < 0
		&& asm_create_hole(data, arg, nb_byte, opcode) < 0)
		return (-1);
	else if (lab_index >= 0)
	{
		content = data->labels[lab_index].buf_position
			- data->instruction_cursor;
		if (nb_byte == 2)
			content = content % 65536;
		if (asm_op_tab(opcode).opcode < 13
			&& asm_op_tab(opcode).opcode > 15)
			content = content % IDX_MOD;
		if (asm_write_in_buf(data, content, nb_byte) < 0)
			return (-1);
	}
	return (1);
}
