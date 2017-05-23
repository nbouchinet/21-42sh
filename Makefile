# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 18:16:06 by zadrien           #+#    #+#              #
#    Updated: 2017/05/23 20:02:26 by zadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean name re

CC= gcc
NAME= 42sh
CFLAGS= -g -Wall -Werror -Wextra
CPATH= srcs/
OPATH= obj/
HPATH= includes/ libft/
INC= $(addprefix -I , $(HPATH))
CFILES= main.c lexer/lex_luthor.c lexer/lexer_check.c lexer/martha_kent.c	\
		lexer/jonathan_kent.c lexer/the_dog.c	\
		AST/oa_sequence.c AST/debug_ast.c AST/pipe_sequence.c AST/creat_ast.c	\
		execution/exec_cmd_seq.c execution/exec_cmd_tools.c execution/get_env.c	\
		builtin/unsetenv.c builtin/setenv.c
		environement/env.c	\

OFILES= $(CFILES:.c=.o)

HFILES= includes/sh21.h includes/AST.h includes/lexer_parser.h includes/exec.h	\
		libft/libft.h	\

OBJ= $(addprefix $(OPATH), $(OFILES))


all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) -ltermcap libft/libft.a -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)/edit_line
	@mkdir -p $(OPATH)/lexer
	@mkdir -p $(OPATH)/AST
	@mkdir -p $(OPATH)/execution
	@mkdir -p $(OPATH)/environement
	@mkdir -p $(OPATH)/builtin
	$(CC) -g -Wall -Werror -Wextra  $(INC) $< -c -o $@

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)
	rm -rf $(OPATH)

re: fclean all

norme:
		@norminette srcs/**/**.[ch]
		@norminette libft/*.[ch]
