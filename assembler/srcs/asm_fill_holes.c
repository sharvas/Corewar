/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_fill_holes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:06:23 by erli              #+#    #+#             */
/*   Updated: 2019/02/19 13:59:46 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

/*
** fills all the remaining holes, if one is not filled, return an error
*/

int		asm_fill_holes(t_asm_data *data)
{
	int i;
	int lab_index;
	int	content;
	int	current_cursor;

	i = 0;
	current_cursor = data->cursor;
	while (i < data->hol_curs)
	{
		data->line = data->holes[i].line;
		if ((lab_index = asm_search_label(data, data->holes[i].name)) < 0)
			return (asm_error_msg(data, LABEL_DOES_NOT_EXIST));
		data->cursor = data->holes[i].buf_position;
		content = data->labels[lab_index].buf_position
			- data->holes[i].instruction_curs;
		if (data->holes[i].nb_byte == 2)
			content = content % 65536;
		if (get_op(data->holes[i].opcode).opcode < 13
			&& get_op(data->holes[i].opcode).opcode > 15)
			content = content % IDX_MOD;
		if (asm_write_in_buf(data, content, data->holes[i++].nb_byte) < 0)
			return (-1);
	}
	data->cursor = current_cursor;
	return (1);
}
