/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_manage_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:56:06 by erli              #+#    #+#             */
/*   Updated: 2019/02/19 13:25:51 by erli             ###   ########.fr       */
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
	char	*strip[MAX_ARGS_NUMBER + 1];
	int		cols[MAX_ARGS_NUMBER];
	int		i;

	if (line[data->col] == '\0' || line[data->col] == COMMENT_CHAR)
		return (0);
	while (line[data->col] == ' ' || line[data->col] == '\t')
		data->col++;
	if (line[data->col] == '\0' || line[data->col] == COMMENT_CHAR)
		return (asm_error_msg(data, MISSING_ARGUMENT));
	ft_bzero(cols, sizeof(int) * MAX_ARGS_NUMBER);
	i = 0;
	while (i <= MAX_ARGS_NUMBER)
		strip[i++] = 0;
	if (asm_strip_arg(data, line, strip, cols) < 0)
		return (-1);
	if (asm_write_instruction(data, opcode, strip, cols) < 0)
		return (-1);
	return (1);
}
