#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erli <erli@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/08 14:34:35 by erli              #+#    #+#              #
#    Updated: 2019/02/19 17:27:50 by erli             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=		../asm

SRCSDIR		=		./srcs
OBJSDIR		=		./objs

SRCS		=		main.c		op.c	asm_assemble.c			asm_get_header2.c	\
					asm_free_data.c		asm_next_line.c								\
					asm_error_msg.c		asm_write_header.c		asm_go_to_tag.c		\
					asm_convert.c		asm_match_tag.c			asm_manage_arg.c	\
					asm_strip_arg.c		asm_verif_arg.c		asm_write_instruction.c	\
					asm_create_ocp.c	asm_atoi_short.c							\
					asm_manage_hole.c	asm_search_label.c		asm_fill_holes.c	\
					asm_write_in_buf.c	asm_dest_file.c								\
					asm_match_name_or_comment.c						\

OBJS		=		$(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

CC			=		gcc -g

CFLAG		=		-Wall -Werror -Wextra

INC			=		includes/
INCL		=		-I includes/ -I libft/includes/ -I ../shared/

HEADER		=		includes/asm.h includes/asm_error_msg.h ../shared/op.h

RM			=		rm -f

LIB			=		libft/libft.a

ADDLIB		=		-L libft/	-lft

GREEN		=		"\033[0;32m"
RED			=		"\033[0;31m"
DEFAULT		=		"\033[0m"

all			:		$(NAME)

$(NAME)		:		$(OBJS) $(LIB) $(HEADER)
					@echo "Compiling:" $(GREEN) $(NAME) $(DEFAULT)
					$(CC) $(CFLAG) $(INCL) $(OBJS) $(ADDLIB)\
					$(FRAMEWORK) -o $(NAME)

$(LIB)		:		
					make -C libft/

$(OBJSDIR)/%.o	:	$(SRCSDIR)/%.c $(HEADER)
					@echo "Compiling:" $(GREEN) $< $(DEFAULT)
					@mkdir -p $(OBJSDIR)
					$(CC) -c $(CFLAG) $(INCL) -c $< -o $@

norm:
	norminette -R CheckForbiddenSourceHeader $(INC) $(SRCSDIR)

clean		:
					@$(RM) $(OBJS)
					@make -C libft clean

fclean		:		clean
					@$(RM) $(NAME)
					@make -C libft fclean

re			:		
					@make -C libft re
					@make fclean
					@make all

delsav		:
					$(RM) *~
					$(RM) */*~
					$(RM) \#*\#
					$(RM) */\#*\#

reset		:		
					@make fclean
					@make delsav
					@make -C libft reset
					@rm -Rf objs

.PHONY		:		clean fclean re delsav reset norm
