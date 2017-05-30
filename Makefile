# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 18:16:06 by zadrien           #+#    #+#              #
#    Updated: 2017/05/29 17:47:47 by khabbar          ###   ########.fr        #
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
CFILES= main.c print_prompt.c signals.c	\
		ft_putast.c \
		lexer/lex_luthor.c lexer/lexer_check.c lexer/martha_kent.c	\
		lexer/jonathan_kent.c lexer/the_dog.c	\
		AST/oa_sequence.c AST/debug_ast.c AST/pipe_sequence.c AST/creat_ast.c	\
		execution/exec_cmd_seq.c execution/exec_cmd_tools.c execution/get_env.c	\
		builtins/unsetenv.c builtins/setenv.c builtins/exit.c builtins/env.c	\
		command_line/arrows.c command_line/cmdl_signals.c command_line/cut_copy_paste.c	\
		command_line/delete.c command_line/get_cmdl.c command_line/heredoc.c	\
		command_line/history_func.c command_line/history.c command_line/pipe_and_or.c	\
		command_line/quotes.c command_line/search_history.c	command_line/winsize.c \
		command_line/set_shell.c execution/exec_qm_seq.c command_line/completion.c

OFILES= $(CFILES:.c=.o)

HFILES= includes/header.h\
		libft/inc/libftprintf.h	\

OBJ= $(addprefix $(OPATH), $(OFILES))


all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) -ltermcap libft/libft.a -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)/command_line
	@mkdir -p $(OPATH)/lexer
	@mkdir -p $(OPATH)/AST
	@mkdir -p $(OPATH)/execution
	@mkdir -p $(OPATH)/environement
	@mkdir -p $(OPATH)/builtins
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
