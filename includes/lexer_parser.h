/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:32:03 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 15:54:43 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H
# include "command_line.h"

/*
********************************************************************************
**									   LEXER								  **
********************************************************************************
*/

typedef struct		s_lex
{
	char			*ch;
	int				type;
}					t_lex;

typedef struct		s_che
{
	char			c;
}					t_che;

typedef struct		s_token
{
	char			*str;
	int				type;
	int				hd;
	struct s_token	*n;
}					t_tok;

typedef struct		s_key
{
	int				i;
	void			(*f)(t_tok**, char**, char*, int*);
}					t_key;

#define NE 1
#define CURR 2

enum				e_token
{
	NONE = 0,
	PIPE = 1,
	QM = 2,
	AND = 4,
	OR = 8,
	CHEVRON = 16,
	IO_N = 32,
	QUOTE = 64,
	SPACE_TOK = 128,
	WORD = 256,
	FIL = 512,
	DQUOTE = 1024,
	LOCAL = 2048,
	BGE = 4096
};

enum				e_dir
{
	RDIR = 8192,
	BDIR = 16384,
	RRDIR = 32768,
	BBDIR = 65536,
	AGRE = 131072,
	BGRE = 262144
};

int					restruct_tok(t_tok **cmd);
t_tok				*init_tok(t_tok **lst, int mod);
void				input(t_tok **cmd);
void				init_token(t_tok **lst);
void				tok_save(t_tok **lst, char **stack, int type);
void				flush(t_tok **lst, char **stack, char *line, int *i);
void				new_parser(t_tok **cmd, char *line, int i);
void				quote(t_tok **lst, char **stack, char *line, int *i);
void				chevron(t_tok **lst, char **stack, char *line, int *i);
void				question_mark(t_tok **lst, char **stack,
					char *line, int *i);
void				pipe_pars(t_tok **lst, char **stack, char *line, int *i);
void				and_pars(t_tok **lst, char **stack, char *line, int *i);
int					arg_check(int ac, int i, char **av, char **envp);
int					io_number(char *str);
void				specified_dir(t_tok **lst);
int					is_space(char c);
int					check_end(char *line);
void				delete_lst(t_tok **cmd);
void				st_tok(char **stack, char c, int reset);
void				input(t_tok **cmd);
void				parser_line(char *line);
void				lexer_check(t_tok **lst);
int					fill_tmp(char tmp[], char c);
void				expanse(t_tok **lst, t_env **env);
t_tok				*heredoc(t_tok **lst);
void				swap_tok(t_tok **lst, t_tok **start, t_tok **next, t_tok **w);
void				replace_tok(t_tok **start, t_tok **next, t_tok **sub, t_tok **sub_end);
int					print_error_lexer(t_tok **lst, t_tok **next, int mod);
#endif
