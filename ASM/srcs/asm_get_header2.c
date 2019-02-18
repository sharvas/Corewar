/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:33:28 by erli              #+#    #+#             */
/*   Updated: 2019/02/18 12:14:49 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <stdlib.h>

static	int			asm_get_string(t_asm_data *data, char *line, int *param)
{
	int	len;

	len = 0;
	while (line[data->col] != '"' && line[data->col] != '\0')
	{
		data->col++;
		len++;
	}
	if (data->header_curs + len + (line[data->col] == '\0' ? 1 : 0)
		> ((*param & 1) ? PROG_NAME_LENGTH : COMMENT_LENGTH))
		return (ft_msg_int(2, "Error, name or comment too long.\n", -1));
	if (line[data->col] == '\0')
		*param = (*param & 1 ? (*param | 4) : (*param | 8));
	else if (line[data->col] == '"')
	{
		line[data->col++] = '\0';
		*param = (*param & 51);
		while (line[data->col] == ' ' || line[data->col] == '\t')
			data->col++;
		if (!(line[data->col] == '\0' || line[data->col] == COMMENT_CHAR))
			return (asm_error_msg(data, SYNTAX_ERROR));
		return (1);
	}
	return (1);
}

static	int			asm_strip_line(t_asm_data *data, char *line, char **strip,
					int *param)
{
	char *str;

	str = "Error, two '.name' or '.comment' instruction.\n";
	while (line[data->col] == ' ' || line[data->col] == '\t')
		data->col++;
	if (line[data->col] == '\0' || line[data->col] == COMMENT_CHAR)
		return (0);
	if (asm_match_name_or_comment(data, line, param) < 0)
		return (-1);
	if (((*param & 1) != 0 && (*param & 16) != 0)
		|| ((*param & 2) != 0 && (*param & 32) != 0))
		return (ft_msg_int(2, str, -1));
	while (line[data->col] == ' ' || line[data->col] == '\t')
		data->col++;
	if (line[data->col++] != '"')
		return (asm_error_msg(data, SYNTAX_ERROR));
	*strip = line + data->col;
	return (asm_get_string(data, line, param));
}

static	int			asm_write_in_header(t_asm_data *data, char *strip,
					t_header *header, int *param)
{
	char *str;

	str = (*param & 1 ? header->prog_name : header->comment);
	ft_strcpy(str + data->header_curs, strip);
	data->header_curs += ft_strlen(strip);
	if ((*param & 12) != 0)
		str[data->header_curs++] = '\n';
	else
	{
		*param += ((*param & 1) == 1 ? 15 : 30);
		data->header_curs = 0;
	}
	return (1);
}

static	int			asm_header_read(t_asm_data *data, char *line,
					t_header *header, int *param)
{
	char	*strip;
	int		ret;

	if (((*param >> 2) & 3) != 0)
	{
		strip = line;
		if ((ret = asm_get_string(data, line, param)) < 0)
			return (-1);
	}
	else if ((ret = asm_strip_line(data, line, &strip, param)) < 0)
		return (-1);
	if (ret == 0)
		return (1);
	if (asm_write_in_header(data, strip, header, param) < 0)
		return (-1);
	return (1);
}

int					asm_get_header(t_asm_data *data, t_header *header, int ret)
{
	char		*line;
	int			param;

	if (data == 0)
		return (-1);
	param = 0;
	line = NULL;
	while (param != 48 && ret > 0)
	{
		ret = asm_next_line(data, &line);
		if (ret > 0)
		{
			data->line++;
			data->col = 0;
			ret = asm_header_read(data, line, header, &param);
			free(line);
		}
		else
			return ((ret == -1 ? ft_msg_int(2, "Failed GNL\n", -2)
				: ft_msg_int(2, "Missing name and/or comment\n", -1)));
	}
	if (ret < 0)
		return (-1);
	return (1);
}
