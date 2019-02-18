# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svaskeli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/04 17:55:10 by svaskeli          #+#    #+#              #
#    Updated: 2019/02/04 17:55:14 by svaskeli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR = corewar

G = -g
FSAN = -fsanitize=address $(G)
FLAGS = -Wall -Werror -Wextra

SRCS_DIR = srcs/
OBJS_DIR = objs/

INC = includes/
HEADER = $(INC)vm.h

LIBFT = libft/ft_printf
LIBFT_A = $(LIBFT)/libftprintf.a

SRCS_FILES = vm_main.c ../../shared/op.c \
	read_args.c read_arg.c read_nbrs.c read_champs.c \
	game.c \
	process.c process_more.c \
	get_args.c get_index.c get_ocp.c \
	op_add_sub.c op_and_or.c op_fork.c op_live_jmp_aff.c \
	op_load.c op_lload.c op_st.c op_sti.c \
	print_error.c print.c print_color.c print_winner.c

SRCS_PATH = $(SRCS_FILES:%=$(SRCS_DIR)%)

OBJS = $(SRCS_FILES:%.c=%.o)
OBJS_PATH = $(addprefix $(OBJS_DIR), $(OBJS))

GREEN = "\033[0;32m"
RED = "\033[0;31m"
DEFAULT = "\033[0m"

all: comp_libft $(COREWAR)

comp_libft:
	@echo "Compiling:" $(GREEN) Libft $(DEFAULT)
	make -C $(LIBFT)

norm:
	norminette -R CheckForbiddenSourceHeader $(INC) $(SRCS_DIR)

fsanitize:
	@echo $(RED)"Compiling all with -g and -fsanitize:" $(COREWAR) $(DEFAULT)
	make -C $(LIBFT)/ fsanitize
	gcc $(FLAGS) $(FSAN) -c $(SRCS_PATH) -I $(INC)
	mkdir -p $(OBJS_DIR)
	mv $(OBJS) $(OBJS_DIR)
	gcc $(FLAGS) $(FSAN) $(OBJS_PATH) $(LIBFT_A) -o $(COREWAR) -I $(LIBFT) -I $(INC)

$(COREWAR): $(LIBFT_A) $(OBJS_DIR) $(OBJS_PATH)
	@echo "Compiling:" $(GREEN) $(COREWAR) $(DEFAULT)
	gcc $(G) $(FLAGS) $(OBJS_PATH) $(LIBFT_A) -o $(COREWAR) -I $(LIBFT) -I $(INC)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	@echo "Compiling:" $(GREEN) $< $(DEFAULT)
	gcc $(G) $(FLAGS) -c $< -o $@ -I $(INC)

clean:
	@make -C $(LIBFT)/ clean
	@rm -rf $(OBJS_DIR)

fclean:
	@make -C $(LIBFT)/ fclean
	@rm -rf $(OBJS_DIR) $(COREWAR)

re: fclean all

.PHONY: all comp_libft norm clean fclean re fsanitize
