/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_go_to_tag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:52:53 by erli              #+#    #+#             */
/*   Updated: 2019/02/18 10:06:10 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <stdlib.h>

static	void	asm_init_labels(t_asm_data *data)
{
	int i;

	i = data->lab_curs;
	while (i < data->lab_size)
	{
		data->labels[i].state = 0;
		i++;
	}
}

static	void	asm_labels_cpy(t_asm_data *data, t_label *new)
{
	int i;

	i = 0;
	while (i < data->lab_curs)
	{
		new[i].name = data->labels[i].name;
		new[i].size = data->labels[i].size;
		new[i].buf_position = data->labels[i].buf_position;
		new[i].line = data->labels[i].line;
		new[i].col = data->labels[i].col;
		new[i].state = data->labels[i].state;
		i++;
	}
}

static	int		asm_malloc_labels(t_asm_data *data)
{
	t_label	*new;

	new = NULL;
	if ((data->lab_size + B_SIZE / 2) > MAX_MALLOC_SIZE)
		return (ft_msg_int(2, "fail, lab_size too big.\n", -1));
	if ((data->mallocked & 1) == 1)
	{
		if (!(new = (t_label *)realloc(data->labels,
				sizeof(t_label) * (data->lab_size + B_SIZE / 2))))
			return (ft_msg_int(2, "failed realloc labels.\n", -1));
		data->labels = new;
		data->lab_size = data->lab_size + B_SIZE / 2;
		asm_init_labels(data);
	}
	else
	{
		if (!(new = (t_label *)malloc(sizeof(t_label) * B_SIZE)))
			return (ft_msg_int(2, "failed malloc labels.\n", -1));
		data->mallocked = (data->mallocked | 1);
		data->lab_size = B_SIZE;
		asm_labels_cpy(data, new);
		data->labels = new;
		asm_init_labels(data);
	}
	return (1);
}

static	int		asm_create_lab(t_asm_data *data, char *line, int i)
{
	int	a;

	if (data->lab_curs >= data->lab_size)
	{
		if (asm_malloc_labels(data) < 0)
			return (-1);
	}
	if (!(data->labels[data->lab_curs].name = ft_strsub(line, data->col, i)))
		return (ft_msg_int(2, "failed malloc label.name\n", -1));
	data->labels[data->lab_curs].size = i;
	data->labels[data->lab_curs].buf_position = data->cursor;
	data->labels[data->lab_curs].line = data->line;
	data->labels[data->lab_curs].col = data->col;
	data->labels[data->lab_curs].state = 1;
	data->lab_curs++;
	a = 0;
	while (a < data->lab_curs - 1)
	{
		if (ft_strcmp(data->labels[a].name,
					data->labels[data->lab_curs - 1].name) == 0)
			return (asm_error_msg(data, 10));
		a++;
	}
	return (1);
}

int				asm_go_to_tag(t_asm_data *data, char *line)
{
	char	*str_lab;
	int		i;

	if (data == 0 || line == 0)
		return (ft_msg_int(2, "no data or no line go to tag.\n", -1));
	while (line[data->col] != '\0' && (line[data->col] == ' ' ||
			line[data->col] == '\t'))
		data->col++;
	str_lab = LABEL_CHARS;
	i = 0;
	while (ft_char_in_str(line[data->col + i], str_lab) == 1)
		i++;
	if (i > 0 && line[data->col + i] == LABEL_CHAR)
	{
		if (asm_create_lab(data, line, i) < 0)
			return (-1);
		data->col = data->col + i + 1;
		while (line[data->col] == ' ' || line[data->col] == '\t')
			data->col++;
	}
	else if (line[data->col] == LABEL_CHAR)
		return (asm_error_msg(data, SYNTAX_ERROR));
	if (line[data->col] == '\0' || line[data->col] == COMMENT_CHAR)
		return (0);
	return (1);
}
