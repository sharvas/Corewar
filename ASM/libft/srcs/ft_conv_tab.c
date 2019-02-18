/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_d_prt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 09:29:36 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 11:34:27 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_conv_d_ptr(t_format *format, va_list ap, t_liststr **list)
{
	if (!ft_strncmp(format->data_format_modifier, "l", 2))
		return (ft_conv_d_ptrdl(format, ap, list));
	else if (!ft_strncmp(format->data_format_modifier, "ll", 2))
		return (ft_conv_d_ptrdll(format, ap, list));
	if (!ft_strncmp(format->data_format_modifier, "h", 2))
		return (ft_conv_d_ptrdh(format, ap, list));
	else if (!ft_strncmp(format->data_format_modifier, "hh", 2))
		return (ft_conv_d_ptrdhh(format, ap, list));
	else
		return (ft_conv_d_ptrd(format, ap, list));
	return (0);
}

int				ft_conv_o_ptr(t_format *format, va_list ap, t_liststr **list)
{
	if (!ft_strncmp(format->data_format_modifier, "l", 2))
		return (ft_conv_o_ptrol(format, ap, list));
	else if (!ft_strncmp(format->data_format_modifier, "ll", 2))
		return (ft_conv_o_ptroll(format, ap, list));
	if (!ft_strncmp(format->data_format_modifier, "h", 2))
		return (ft_conv_o_ptroh(format, ap, list));
	else if (!ft_strncmp(format->data_format_modifier, "hh", 2))
		return (ft_conv_o_ptrohh(format, ap, list));
	else
		return (ft_conv_o_ptro(format, ap, list));
	return (0);
}

int				ft_conv_f_ptr(t_format *format, va_list ap, t_liststr **list)
{
	if (!ft_strncmp(format->data_format_modifier, "l", 2))
		return (ft_conv_f_ptrfl(format, ap, list));
	else if (!ft_strncmp(format->data_format_modifier, "L", 2))
		return (ft_conv_f_ptrfbigl(format, ap, list));
	else
		return (ft_conv_f_ptrfl(format, ap, list));
	return (0);
}

int				ft_conv_e_ptr(t_format *format, va_list ap, t_liststr **list)
{
	if (!ft_strncmp(format->data_format_modifier, "l", 2))
		return (ft_conv_e_ptrel(format, ap, list));
	else if (!ft_strncmp(format->data_format_modifier, "L", 2))
		return (ft_conv_e_ptrebigl(format, ap, list));
	else
		return (ft_conv_e_ptrel(format, ap, list));
	return (0);
}

int				ft_conv_g_ptr(t_format *format, va_list ap, t_liststr **list)
{
	if (!ft_strncmp(format->data_format_modifier, "l", 2))
		return (ft_conv_g_ptrgl(format, ap, list));
	else if (!ft_strncmp(format->data_format_modifier, "L", 2))
		return (ft_conv_g_ptrgbigl(format, ap, list));
	else
		return (ft_conv_g_ptrgl(format, ap, list));
	return (0);
}
