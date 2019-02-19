/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_verif_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:26:30 by erli              #+#    #+#             */
/*   Updated: 2019/02/19 14:00:22 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

/*
** Verify that there is the right amout of argument, of the right type for
** the instruction by looking in g_op_tab[opcode]
** return(ocp)
*/

int				asm_verif_reg(char *strip)
{
	int	i;
	int	cpt;

	i = 1;
	cpt = 0;
	if (strip[0] != 'r')
		return (0);
	while (strip[i] == '0')
		i++;
	while (strip[i + cpt] != '\0' && ft_isdigit(strip[i + cpt]) == 1)
		cpt++;
	if (cpt > 3 || strip[i + cpt] != '\0')
		return (-1);
	cpt = ft_atoi(strip + i);
	if (cpt < 0 || cpt > 255)
		return (-1);
	return (1);
}

int				asm_verif_dir_ind(char *strip, int dir, int i)
{
	char	*str_lab;

	str_lab = LABEL_CHARS;
	if (dir == 1 && strip[i] != DIRECT_CHAR)
		return (0);
	else if (dir == 1)
		i++;
	if (strip[i] == LABEL_CHAR)
	{
		i++;
		while (ft_char_in_str(strip[i], str_lab) == 1)
			i++;
		if (strip[i] == '\0')
			return (1);
		return (-1);
	}
	i = strip[i] == '-' || strip[i] == '+' ? i + 1 : i;
	if (ft_isdigit(strip[i]) == 0)
		return (-1);
	while (ft_isdigit(strip[i]) == 1)
		i++;
	if (strip[i] == '\0')
		return (1);
	return (-1);
}

int				asm_verif_type_arg(t_asm_data *data, t_op op,
					char **strip, int i)
{
	int	tr;

	tr = 0;
	if ((T_REG & op.arg_type[i]) > 0)
	{
		if ((tr = asm_verif_reg(strip[i])) == -1)
			return (asm_error_msg(data, WRONG_REG_NUMBER));
	}
	if (tr == 0 && (T_DIR & op.arg_type[i]) > 0)
	{
		if ((tr = asm_verif_dir_ind(strip[i], 1, 0)) == -1)
			return (asm_error_msg(data, LEXICAL_ERROR));
		tr = tr == 1 ? tr + 1 : tr;
	}
	if (tr == 0 && (T_IND & op.arg_type[i]) > 0)
	{
		if ((tr = asm_verif_dir_ind(strip[i], 0, 0)) == -1)
			return (asm_error_msg(data, LEXICAL_ERROR));
		tr = tr == 1 ? tr + 2 : tr;
	}
	return (tr);
}

int				asm_verif_nb_arg(t_asm_data *data, int opcode,
					char **strip, int *cols)
{
	int		i;
	int		tr;
	char	ocp;

	i = 0;
	ocp = 0;
	while (strip[i] != NULL && strip[i][0] != COMMENT_CHAR)
		i++;
	if (get_op(opcode).nb_arg != i)
		return (asm_error_msg(data, WRONG_NB_OF_ARG));
	i = 0;
	while (i < get_op(opcode).nb_arg)
	{
		data->col = cols[i];
		if ((tr = asm_verif_type_arg(data, get_op(opcode), strip, i)) <= 0)
		{
			if (tr == -1)
				return (1);
			return (asm_error_msg(data, WRONG_ARG_TYPE));
		}
		asm_create_ocp(&ocp, tr, i);
		i++;
	}
	return (ocp);
}

char			asm_verif_arg(t_asm_data *data, int opcode,
					char **strip, int *cols)
{
	char	ocp;

	ocp = 0;
	if (data == 0 || opcode == -1 || strip == 0)
		return (1);
	ocp = asm_verif_nb_arg(data, opcode, strip, cols);
	if (ocp & 1)
		return (1);
	return (ocp);
}
