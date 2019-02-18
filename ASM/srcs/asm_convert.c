/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 09:40:26 by erli              #+#    #+#             */
/*   Updated: 2019/02/18 12:14:40 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <stdlib.h>

/*
** parcour le fichier .s ligne par ligne en decodant les instructions,
** en stockant les label et les trous, et en remplissant les trou.
** retourne le bon message d'erreur si erreur.
*/

int		asm_convert(t_asm_data *data)
{
	char	*line;
	int		ret;
	char	opcode;

	line = NULL;
	while ((ret = asm_next_line(data, &line)) > 0)
	{
		data->line++;
		data->col = 0;
		data->instruction_cursor = data->cursor;
		if (asm_go_to_tag(data, line) < 0)
			ret = -1;
		if (ret > 0 && (opcode = asm_match_tag(data, line)) < 0)
			ret = -1;
		if (ret > 0 && asm_manage_arg(data, opcode, line) < 0)
			ret = -1;
		free(line);
		if (ret < 0)
			return (-1);
	}
	if (ret < 0)
		return (ft_msg_int(2, "Failed GNL.\n", -1));
	if (ret == 0 && data->cursor == 0)
		return (asm_error_msg(data, NO_INSTRUCTION));
	return (1);
}
