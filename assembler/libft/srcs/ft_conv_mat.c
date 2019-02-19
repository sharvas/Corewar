/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_d_prt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 09:29:36 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 11:26:12 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_conv_d_mat(t_format *format, va_list ap, t_liststr **list)
{
	if (!ft_strncmp(format->data_format_modifier, "l", 2))
		return (ft_conv_d_matdl(format, ap, list));
	else if (!ft_strncmp(format->data_format_modifier, "ll", 2))
		return (ft_conv_d_matdll(format, ap, list));
	if (!ft_strncmp(format->data_format_modifier, "h", 2))
		return (ft_conv_d_matdh(format, ap, list));
	else if (!ft_strncmp(format->data_format_modifier, "hh", 2))
		return (ft_conv_d_matdhh(format, ap, list));
	else
		return (ft_conv_d_matd(format, ap, list));
	return (0);
}

int				ft_conv_o_mat(t_format *format, va_list ap, t_liststr **list)
{
	if (!ft_strncmp(format->data_format_modifier, "l", 2))
		return (ft_conv_o_matol(format, ap, list));
	else if (!ft_strncmp(format->data_format_modifier, "ll", 2))
		return (ft_conv_o_matoll(format, ap, list));
	if (!ft_strncmp(format->data_format_modifier, "h", 2))
		return (ft_conv_o_matoh(format, ap, list));
	else if (!ft_strncmp(format->data_format_modifier, "hh", 2))
		return (ft_conv_o_matohh(format, ap, list));
	else
		return (ft_conv_o_mato(format, ap, list));
	return (0);
}

int				ft_conv_f_mat(t_format *format, va_list ap, t_liststr **list)
{
	if (!ft_strncmp(format->data_format_modifier, "l", 2))
		return (ft_conv_f_matfl(format, ap, list));
	else if (!ft_strncmp(format->data_format_modifier, "L", 2))
		return (ft_conv_f_matfbigl(format, ap, list));
	else
		return (ft_conv_f_matfl(format, ap, list));
	return (0);
}
