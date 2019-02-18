#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erli <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/14 17:45:59 by erli              #+#    #+#              #
#    Updated: 2019/01/21 13:33:24 by erli             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=		libft.a

SRCSDIR		=		srcs

OBJSDIR		=		objs

SRCS		=		ft_atoi.c			ft_char_at_pos.c	ft_itoa.c			\
					ft_char_in_str.c	ft_free_mat_int.c	get_next_line.c		\
					ft_tolower.c		ft_toupper.c		ft_free_mat_char.c	\
					ft_isalpha.c		ft_isdigit.c		ft_isalnum.c		\
					ft_isascii.c		ft_isprint.c		ft_msg_int.c		\
					ft_msg_ptr.c		ft_dtoa.c			ft_ldtoa.c			\
					ft_int_in_ptr.c		ft_swap_int.c		ft_swap_str.c		\
															ft_str_made_of_str.c\
					ft_merge_sort_tab.c	ft_merge_sort_tab_str.c					\
																				\
					ft_bzero.c			ft_memalloc.c		ft_memalloc_c.c		\
					ft_memccpy.c		ft_memchr.c			ft_memcmp.c			\
					ft_memcpy.c			ft_memdel.c			ft_memmove.c		\
					ft_memset.c													\
																				\
					ft_printstrsplit.c	ft_putchar.c		ft_putchar_fd.c		\
					ft_putendl.c		ft_putendl_fd.c		ft_putnbr.c			\
					ft_putnbr_fd.c		ft_putstr.c			ft_putstr_fd.c		\
																				\
					ft_strcat.c			ft_strchr.c			ft_strclr.c			\
					ft_strcmp.c			ft_strcpy.c			ft_strdel.c			\
					ft_strdup.c			ft_strequ.c			ft_striter.c		\
					ft_striteri.c		ft_strjoin.c		ft_strjoinfree.c	\
					ft_strlcat.c		ft_strlen.c			ft_strmap.c			\
					ft_strmapi.c		ft_strncat.c		ft_strncmp.c		\
					ft_strncpy.c		ft_strnequ.c		ft_strnew.c			\
					ft_strnstr.c		ft_strrchr.c		ft_strsplit.c		\
					ft_strstr.c			ft_strsub.c			ft_str_to_lower.c	\
					ft_str_to_upper.c	ft_strtrim.c							\
																				\
					ft_printf.c													\
					ft_conv_c.c			ft_conv_c_matc.c	ft_conv_c_ptrc.c	\
					ft_conv_d.c			ft_conv_d_matd.c	ft_conv_d_matdh.c	\
					ft_conv_d_matdhh.c	ft_conv_d_matdl.c	ft_conv_d_matdll.c	\
					ft_conv_d_ptrd.c	ft_conv_d_ptrdh.c	ft_conv_d_ptrdhh.c	\
					ft_conv_d_ptrdl.c	ft_conv_d_ptrdll.c	ft_conv_e.c			\
					ft_conv_big_e.c		ft_conv_e_ptrel.c	ft_conv_e_ptrebigl.c\
					ft_conv_f.c			ft_conv_f_matfl.c	ft_conv_f_matfbigl.c\
					ft_conv_f_ptrfl.c	ft_conv_f_ptrfbigl.c					\
					ft_conv_g.c			ft_conv_g_ptrgl.c	ft_conv_g_ptrgbigl.c\
					ft_conv_mat.c		ft_conv_not.c		ft_conv_o.c			\
					ft_conv_o_mato.c	ft_conv_o_matoh.c	ft_conv_o_matohh.c	\
					ft_conv_o_matol.c	ft_conv_o_matoll.c	ft_conv_o_ptro.c	\
					ft_conv_o_ptroh.c	ft_conv_o_ptrohh.c	ft_conv_o_ptrol.c	\
					ft_conv_o_ptroll.c	ft_conv_p.c			ft_conv_p_matp.c	\
					ft_conv_p_ptrp.c	ft_conv_percent.c	ft_conv_s.c			\
					ft_conv_s_mats.c	ft_conv_s_ptrs.c	ft_conv_tab.c		\
					ft_conv_u.c			ft_conv_x.c			ft_conv_big_x.c		\
					ft_free_format.c	ft_liststr_manip.c	ft_loophole.c		\
					get_converter.c		init_format.c		manage_format.c		\
					printf_util.c

OBJS		=		$(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

CC			=		gcc

CFLAG		=		-Wall -Werror -Wextra

INCL		=		-I includes/

RM			=		rm -f


all			:		$(NAME)

$(NAME)		:		$(OBJS) includes/libft.h includes/ft_con_tab.h 		\
					includes/get_next_line.h
					ar -rucs $(NAME) $(OBJS)

$(OBJSDIR)/%.o			:		$(SRCSDIR)/%.c
					@mkdir -p $(OBJSDIR)
					$(CC) $(CFLAG) $(INCL) -c $< -o $@

val			:		$(OBJS) includes/libft.h includes/ft_con_tab.h		\
					includes/get_next_line.h
					$(CC) -g $(CFLAG) $(INCL) -o test $(OBJS) main.c -L.  -lft

clean		:
					@$(RM) $(OBJS)

fclean		:		clean
					@$(RM) $(NAME)

re			:
					@make fclean
					@make all

delsav		:
					@$(RM) */*~
					@$(RM) *~
					@$(RM) \#*\#
					@$(RM) */\#*\#

reset		:
					@make fclean
					@make delsav
					@rm -Rf objs/

.PHONY		:		clean delsav re fclean reset
