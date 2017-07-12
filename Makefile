# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 18:16:06 by zadrien           #+#    #+#              #
#    Updated: 2017/07/10 17:40:38 by khabbar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
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

CFILES= main.c print_prompt.c signals.c ft_putast.c	\
		lexer/lex_luthor.c lexer/lexer_check.c lexer/martha_kent.c lexer/expanse.c \
		lexer/jonathan_kent.c lexer/the_dog.c AST/ast_tools.c AST/creat_ast.c \
		AST/creat_io_seq.c AST/creat_pipe_seq.c AST/creat_qm_oa.c AST/destroy_ast.c \
		init_env/check_env.c \
		execution/bin_fin_help2.c execution/bin_fin_helper.c execution/binary_finders.c	\
		execution/env_tools.c execution/exec_seq.c execution/exec_tools.c \
		execution/get_env.c execution/main_exec.c execution/redirection.c \
		builtins/unsetenv.c builtins/setenv.c builtins/env.c builtins/ft_echo.c \
		builtins/ft_exit.c builtins/history.c builtins/history_opt.c  lexer/bang_bang.c \
		lexer/bang_sub.c builtins/hash.c builtins/hash_tools.c builtins/builtin_hash.c \
		command_line/arrows.c command_line/cmdl_signals.c command_line/cut_copy_paste.c	\
		command_line/delete.c command_line/get_cmdl.c command_line/heredoc.c	\
		command_line/history_func.c command_line/history.c command_line/pipe_and_or.c	\
		command_line/quotes.c command_line/search_history.c \
		command_line/set_shell.c command_line/completion.c \
		command_line/completion_func.c command_line/completion_func2.c \
		command_line/completion_list.c command_line/tmp_pipe.c builtins/cd.c \
		command_line/ctrl_l.c command_line/heredoc_func.c \

OFILES= $(CFILES:.c=.o)

HFILES= includes/header.h \
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
	@mkdir -p $(OPATH)/init_env
	$(CC) $(CFLAGS)  $(INC) $< -c -o $@

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
