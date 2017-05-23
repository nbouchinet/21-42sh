/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 13:56:06 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/23 13:03:47 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define  SH21_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include "../libft/libft.h"

# define DELETE 127
# define DELETE_BW 2117294875
# define A_UP 4283163
# define A_DW 4348699
# define A_RG 4414235
# define A_LF 4479771
# define ENTER 10
# define SPACE 32
# define ESC 27
# define EXECUTABLE     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define CARACDEV           "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define LINK               "\x1b[35m"
# define DIRECTORY          "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"
// # define malloc(x) NULL   FAIT BIEN LES CHOSE
/*
******************************************************
**                       LEXER                     **
**                 LL - JK - MK - TD              **
***************************************************
*/

typedef struct		s_che
{
	char			c;
}					t_che;

typedef struct		s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}					t_tok;

typedef struct		s_key
{
	int				i;
	void			(*f)(t_tok**, char**, char*, int*);
}					t_key;

enum 				e_token
{
	PIPE = 1,
	QM,
	AND,
	OR,
	CHEVRON,
	IO_NUMBER,
	QUOTE,
	SPACE_TOK,
	WORD
};

enum				e_dir
{
	RDIR = 22,
	BDIR,
	RRDIR,
	BBDIR
};

void				init_token(t_tok **lst);
void				tok_save(t_tok **lst, char **stack, int type);
void				flush(t_tok **lst, char **stack, char *line, int *i);
void				new_parser(t_tok **cmd, char *line);
void				quote(t_tok **lst, char **stack, char *line, int *i);
void				chevron(t_tok **lst, char **stack, char *line, int *i);
void				question_mark(t_tok **lst, char **stack, char *line, int *i);
void				pipe_pars(t_tok **lst, char **stack, char *line, int *i);
void				and_pars(t_tok **lst, char **stack, char *line, int *i);
int					arg_check(int ac, int i, char **av, char **envp);
int					io_number(char *str);
int					is_space(char c);
int					check_end(char *line);
void				delete_lst(t_tok **cmd);
void				st_tok(char **stack, char c);
void				input(t_tok **cmd);
void				parser_line(char *line);
int					lexer_check(t_tok **lst);
void				delete_lstenv(t_env **cmd);
/*
******************************************************
**               Abstract Syntax Tree              **
**          t_ast = first lvl of parsing          **
**                                               **
**************************************************
*/

enum 			e_ast
{
	QM_SEQ = 42,
	CMD_SEQ,
	PIPE_SEQ,
	AND_OR,
	IO_SEQ,
	CMD_NAME,
	SIMP_CMD,
	CMD_ARG
};

typedef struct		s_ast
{
	char			*str;
	int				type;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

void	init_ast(t_ast **ast, char *str, int type);
int		cmd_seq(t_ast **ast, t_env **env); // Implent lst_env
void	simple_command(t_ast **ast);
int		exec_oa_sequence(t_ast **ast, t_env **env); // Implent lst_env
void	simple_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
void	command_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
t_tok	*find_andor_tok(t_tok **lst, t_tok **stop);
void	oa_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
t_tok	*find_pipe_tok(t_tok **lst, t_tok **stop);
void	pipe_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
int		exec_pipe_sequence(t_ast **ast, t_env **env); // Implent lst_env
void	exec_ast(t_ast **ast, t_env **env); // Implent lst_env
void	primary_sequence(t_ast **ast, t_tok **lst);
void	secondary_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
void	tertiary_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
// typedef struct		s_state
// {
// 	int				type;
// 	void			(*f)(t_ast**, t_tok**, t_tok **tmp)
// }					t_state;

/*
*****************************************
**              EXECUTION             **
***************************************
*/
int		exec_cmd_seq(t_ast **ast, t_env **env); // Keep the path ?
char	**creat_arg(t_ast **ast, char *cmd);
int		time_4_magic(char **arg, char **env);
int		exec_abs_cmd(t_ast **ast, t_env **env);
int		exec_rlt_cmd(t_ast **ast, t_env **env);
int		exec_binary(t_ast **ast, t_env **env);
// void	ft_freetab(char **trash);
char	*get_dir(char *cmd);
int		ft_checkbin(DIR *dir, char *cmd);
int		binary_finder(char *path, char *cmd);
int		find_bin(t_ast **ast);
char	*binary_find(char *cmd, char **path);
int		find_cmd_bin(t_ast **ast, char **path);
int		count_arg_node(t_ast **ast);
int		seak(char *s);
char	*var_value(int i, char *var, char *value);
void	reduc_shlvl(t_env **env, char *s);
void	increase_shlvl(t_env **env);
char	**get_env(t_env **lst, char *s);
int		isexec(char *path);
char	*create_path(char *env, char *cmd);

/*
*****************************************
**                       ENV          **
***************************************
*/

void				print_env(t_env *lst);
void				ft_freetab(char **tob);
void				init_env(t_env **lst, char **env);
int					ft_unsetenv(t_ast **ast, t_env **env);
int					ft_env(t_ast **ast, t_env **env);
int					ft_setenv(t_ast **lst, t_env **env);
char				**creat_arg_env(t_ast **ast);
int					countab(char **tob);
#endif
