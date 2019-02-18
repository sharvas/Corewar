/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_manage_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:56:06 by erli              #+#    #+#             */
/*   Updated: 2019/02/18 10:23:15 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

/*
** gere les parametres de l'instructions et les ecris dans buf
** retourne 1 si tout va bien, un message d'erreur correspondant sinon
** gere aussi les commentaires en fin de ligne
*/

int			asm_manage_arg(t_asm_data *data, int opcode, char *line)
{
	char	*strip[4];
	int		cols[3];
	int		i;

	if (line[data->col] == '\0' || line[data->col] == COMMENT_CHAR)
		return (0);
	while (line[data->col] == ' ' || line[data->col] == '\t')
		data->col++;
	if (line[data->col] == '\0' || line[data->col] == COMMENT_CHAR)
		return (asm_error_msg(data, MISSING_ARGUMENT));
	ft_bzero(cols, sizeof(int) * 3);
	i = 0;
	while (i <= 3)
		strip[i++] = 0;
	if (asm_strip_arg(data, line, strip, cols) < 0)
		return (-1);
	if (asm_write_instruction(data, opcode, strip, cols) < 0)
		return (-1);
	return (1);
}
