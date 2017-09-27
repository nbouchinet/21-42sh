# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 18:16:06 by zadrien           #+#    #+#              #
#    Updated: 2017/09/27 11:10:24 by khabbar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:			all clean fclean name re

CC=				gcc

NAME=			42sh

CFLAGS=			-g -Wall -Werror -Wextra

CPATH=			srcs/

OPATH=			obj/

HPATH=			includes/ libft/

INC=			$(addprefix -I , $(HPATH))

CFILES= 		main.c \
				print_prompt.c \
				signals.c	\
				lexer/lex_luthor.c \
				lexer/lexer_check.c \
				lexer/martha_kent.c \
				lexer/expanse.c \
				lexer/jonathan_kent.c \
				lexer/the_dog.c \
				AST/ast_tools.c \
				AST/creat_ast.c \
				AST/creat_io_seq.c \
				AST/creat_pipe_seq.c \
				AST/creat_qm_oa.c \
				AST/destroy_ast.c \
				AST/creat_bg_seq.c \
				init_env/check_env.c \
				execution/bin_fin_help2.c \
				execution/bin_fin_helper.c \
				execution/binary_finders.c	\
				execution/env_tools.c \
				execution/exec_seq.c \
				execution/exec_tools.c \
				execution/get_env.c \
				execution/main_exec.c \
				execution/redirection.c \
				builtins/cd.c \
				builtins/unsetenv.c \
				builtins/setenv.c \
				builtins/env.c \
				builtins/echo.c \
				builtins/exit.c \
				builtins/hash.c \
				builtins/hash_tools.c \
				builtins/builtin_hash.c \
				builtins/local.c \
				builtins/unset.c \
				builtins/export.c \
				builtins/history.c \
				builtins/history_opt.c \
				builtins/history_opt2.c \
				builtins/read.c \
				builtins/fg.c \
				builtins/read_opt1.c \
				command_line/arrows_fucn1.c \
				command_line/arrows_fucn2.c \
				command_line/bang.c \
				command_line/bang_parse.c \
				command_line/bang_sub.c \
				command_line/ccp.c \
				command_line/ccp_paste.c \
				command_line/check_env.c \
				command_line/cmdl_signals.c \
				command_line/completion.c \
				command_line/completion_display.c \
				command_line/completion_display2.c \
				command_line/completion_edit.c \
				command_line/completion_func.c \
				command_line/completion_move.c \
				command_line/ctrl.c \
				command_line/del_all.c \
				command_line/delete.c \
				command_line/esc.c \
				command_line/get_cmdl.c \
				command_line/history.c \
				command_line/inhibiteur.c \
				command_line/iris_west.c \
				command_line/pipe_and_or.c \
				command_line/print.c \
				command_line/quotes.c \
				command_line/return.c \
				command_line/search_history.c \
				command_line/set_shell.c \
				command_line/slg.c \
				job_control/creat_process.c \
				job_control/foreground.c \
				job_control/init_tools.c \
				job_control/job_control.c \
				job_control/job_exec_seq.c \
				job_control/job_exec.c \
				job_control/job_handle_utils.c \
				job_control/job_handle.c \
				job_control/job_pipe.c \
				job_control/job_tools.c \
				job_control/catch_error.c \
				job_control/job_bg_seq.c \
				job_control/job_env.c \
				job_control/env_tools.c \
				job_control/env_utils.c \
				job_control/env_utils2.c \
				job_control/kill_job.c \

OFILES=			$(CFILES:.c=.o)

HFILES=			includes/header.h \
				libft/inc/libftprintf.h	\

OBJ=			$(addprefix $(OPATH), $(OFILES))


all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) -ltermcap libft/libft.a -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)/command_line
	@mkdir -p $(OPATH)/command_line/bang
	@mkdir -p $(OPATH)/command_line/completion
	@mkdir -p $(OPATH)/command_line/history
	@mkdir -p $(OPATH)/command_line/heredoc
	@mkdir -p $(OPATH)/command_line/pipe_and_or_quote
	@mkdir -p $(OPATH)/lexer
	@mkdir -p $(OPATH)/AST
	@mkdir -p $(OPATH)/execution
	@mkdir -p $(OPATH)/environement
	@mkdir -p $(OPATH)/builtins
	@mkdir -p $(OPATH)/init_env
	@mkdir -p $(OPATH)/job_control
	$(CC) $(CFLAGS)  $(INC) $< -c -o $@

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)
	rm -rf $(OPATH)
	rm srcs/.42sh_history

re: fclean all

norme:
	@norminette srcs/**/**.[ch]
	@norminette libft/*.[ch]
