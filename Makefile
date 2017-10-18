# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 18:16:06 by zadrien           #+#    #+#              #
#    Updated: 2017/10/17 18:26:17 by zadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:			all clean fclean name re

CC=				gcc

NAME=			42sh

CFLAGS=			-g3 -Wall -Werror -Wextra #-fsanitize=address

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
				lexer/jonathan_kent.c \
				lexer/the_dog.c \
				lexer/misc_lexer.c \
				lexer/expanse.c \
				lexer/misc_exp.c \
				AST/ast_tools.c \
				AST/creat_ast.c \
				AST/creat_io_seq.c \
				AST/creat_pipe_seq.c \
				AST/creat_qm_oa.c \
				AST/destroy_ast.c \
				AST/creat_bg_seq.c \
				AST/misc_ast.c \
				init_env/check_env.c \
				builtins/cd.c \
				builtins/cd_func.c \
				builtins/unsetenv.c \
				builtins/unsetenv_tools.c \
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
				builtins/read_parse.c \
				builtins/read_opt1.c \
				builtins/read_opt2.c \
				builtins/fg.c \
				builtins/hash_clean.c \
				builtins/misc_builtins.c \
				command_line/arrows_fucn1.c \
				command_line/arrows_fucn2.c \
				command_line/bang.c \
				command_line/bang_parse.c \
				command_line/bang_check_ed.c \
				command_line/bang_sub.c \
				command_line/clear.c \
				command_line/ccp.c \
				command_line/ccp_paste.c \
				command_line/cmdl_signals.c \
				command_line/completion.c \
				command_line/completion_display.c \
				command_line/completion_display2.c \
				command_line/completion_edit.c \
				command_line/completion_func.c \
				command_line/completion_func2.c \
				command_line/completion_move.c \
				command_line/ctrl.c \
				command_line/del_all.c \
				command_line/delete.c \
				command_line/esc.c \
				command_line/get_cmdl.c \
				command_line/graphical_print.c \
				command_line/history.c \
				command_line/handle_ctrlc.c \
				command_line/inhibiteur.c \
				command_line/pipe_and_or.c \
				command_line/print.c \
				command_line/quotes.c \
				command_line/return.c \
				command_line/resize_win.c \
				command_line/search_history.c \
				command_line/set_shell.c \
				command_line/slg.c \
				command_line/misc_cmdl.c \
				job_control/ast_base.c \
				job_control/ast_seq.c \
				job_control/catch_error.c \
				job_control/creat_job.c \
				job_control/creat_job_name.c \
				job_control/delete_job.c \
				job_control/env_builtin.c \
				job_control/exec_env.c \
				job_control/exec_env_tools.c \
				job_control/fg_bg.c \
				job_control/fork_fg.c \
				job_control/fork_bg.c \
				job_control/fork_utils.c \
				job_control/heredoc.c \
				job_control/heredoc_func.c \
				job_control/job_control.c \
				job_control/job_control_tools.c \
				job_control/job_tools.c \
				job_control/misc.c \
				job_control/misc_2.c \
				job_control/pipe_exec.c \
				job_control/shlvl.c \
				job_control/redirection.c \
				job_control/misc_rdir.c \
				job_control/find_bin.c \
				job_control/env_pipe.c \
				job_control/find_bin_tools.c \
				job_control/job_message.c \


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

re: fclean all

norme:
	@norminette srcs/**/**.[ch]
	@norminette libft/*.[ch]
