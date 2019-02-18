/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <erli@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 13:28:45 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 10:20:27 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		init_format(t_format **format)
{
	if (!(*format = (t_format *)malloc(sizeof(t_format))))
		return (-1);
	(*format)->pound = 0;
	(*format)->plus = 0;
	(*format)->minus = 0;
	(*format)->zero = 0;
	(*format)->space = 0;
	(*format)->pointer = 0;
	(*format)->m_width = -1;
	(*format)->precision = -1;
	if (!((*format)->data_format_modifier = (char *)malloc(sizeof(char) * 3)))
		return (-1);
	(*format)->data_format_modifier[0] = '\0';
	(*format)->data_format_modifier[1] = '\0';
	(*format)->data_format_modifier[2] = '\0';
	(*format)->conversion = '\0';
	return (1);
}

int		copy_format(t_format **format, t_format *source)
{
	if (!(*format = (t_format *)malloc(sizeof(t_format))))
		return (-1);
	(*format)->pound = source->pound;
	(*format)->plus = source->plus;
	(*format)->minus = source->minus;
	(*format)->zero = source->zero;
	(*format)->space = source->space;
	(*format)->pointer = source->pointer;
	(*format)->m_width = source->m_width;
	(*format)->precision = source->precision;
	if (!((*format)->data_format_modifier = (char *)malloc(sizeof(char) * 3)))
		return (-1);
	(*format)->data_format_modifier[0] = source->data_format_modifier[0];
	(*format)->data_format_modifier[1] = source->data_format_modifier[1];
	(*format)->data_format_modifier[2] = source->data_format_modifier[2];
	(*format)->conversion = source->conversion;
	return (1);
}
