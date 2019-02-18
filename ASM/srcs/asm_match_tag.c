/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_match_tag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:26:03 by erli              #+#    #+#             */
/*   Updated: 2019/02/18 11:16:18 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

/*
** line[data->col] doit pointer sur un tag,
** retourne le opcode si ca match,
** retourne -1 ou 20 si erreur avec message d'erreur LEXICAL ERROR pointant
** au debut du mot
** gere les ligne vide
*/

int		asm_match_tag(t_asm_data *data, char *line)
{
	unsigned int	i;
	int				j;

	if (line[data->col] == '\0' || line[data->col] == COMMENT_CHAR)
		return (0);
	i = data->col;
	while (line[i] != ' ' && ((int)i - data->col) < data->tag_max_size
		&& line[i] != '\t' && line[i] != '\0' && line[i] != COMMENT_CHAR)
		i++;
	if (line[i] == '\0' || line[i] == COMMENT_CHAR)
		return (asm_error_msg(data, LEXICAL_ERROR));
	line[i++] = '\0';
	j = 0;
	while (asm_op_tab(j).tag != 0)
	{
		if (ft_strcmp(line + data->col, asm_op_tab(j).tag) == 0)
		{
			data->col = i;
			return (j);
		}
		j++;
	}
	return ((char)asm_error_msg(data, LEXICAL_ERROR));
}
