/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_con_tab.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erli <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 11:20:49 by erli              #+#    #+#             */
/*   Updated: 2018/11/29 10:35:54 by erli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CON_TAB_H
# define FT_CON_TAB_H

# include "libft.h"

t_conv	g_conv_tab[] =
{
	{'c', &ft_conv_c},
	{'s', &ft_conv_s},
	{'p', &ft_conv_p},
	{'d', &ft_conv_d},
	{'i', &ft_conv_d},
	{'o', &ft_conv_o},
	{'u', &ft_conv_u},
	{'x', &ft_conv_x},
	{'X', &ft_conv_big_x},
	{'f', &ft_conv_f},
	{'F', &ft_conv_f},
	{'e', &ft_conv_e},
	{'E', &ft_conv_big_e},
	{'g', &ft_conv_g},
	{'%', &ft_conv_percent},
	{'\0', &ft_conv_not}
};

t_conv	g_conv_tab_ptr[] =
{
	{'c', &ft_conv_c_ptrc},
	{'s', &ft_conv_s_ptrs},
	{'p', &ft_conv_p_ptrp},
	{'d', &ft_conv_d_ptr},
	{'i', &ft_conv_d_ptr},
	{'o', &ft_conv_o_ptr},
	{'u', &ft_conv_o_ptr},
	{'x', &ft_conv_o_ptr},
	{'X', &ft_conv_o_ptr},
	{'f', &ft_conv_f_ptr},
	{'F', &ft_conv_f_ptr},
	{'e', &ft_conv_e_ptr},
	{'E', &ft_conv_e_ptr},
	{'g', &ft_conv_g_ptr},
	{'\0', &ft_conv_not}
};

t_conv	g_conv_tab_mat[] =
{
	{'c', &ft_conv_c_matc},
	{'s', &ft_conv_s_mats},
	{'p', &ft_conv_p_matp},
	{'d', &ft_conv_d_mat},
	{'i', &ft_conv_d_mat},
	{'o', &ft_conv_o_mat},
	{'u', &ft_conv_o_mat},
	{'x', &ft_conv_o_mat},
	{'X', &ft_conv_o_mat},
	{'f', &ft_conv_f_mat},
	{'F', &ft_conv_f_mat},
	{'e', &ft_conv_f_mat},
	{'E', &ft_conv_f_mat},
	{'g', &ft_conv_f_mat},
	{'\0', &ft_conv_not}
};

#endif
