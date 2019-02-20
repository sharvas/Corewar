# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svaskeli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/19 19:39:06 by svaskeli          #+#    #+#              #
#    Updated: 2019/02/20 09:31:39 by erli             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm
COREWAR = corewar
NAME = $(ASM) $(COREWAR)

ASM_DIR = assembler
COREWAR_DIR = virtual_machine

all: $(NAME)

norm:
	@make -C $(ASM_DIR)/ norm
	@make -C $(COREWAR_DIR)/ norm

comp_asm:
	@make -C $(ASM_DIR)/

comp_corewar:
	@make -C $(COREWAR_DIR)/

$(NAME): comp_asm comp_corewar

clean:
	@make -C $(ASM_DIR)/ clean
	@make -C $(COREWAR_DIR)/ clean

fclean:
	@make -C $(ASM_DIR)/ fclean
	@make -C $(COREWAR_DIR)/ fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all comp_asm comp_corewar clean fclean re norm
