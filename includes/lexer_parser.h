/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:32:03 by zadrien           #+#    #+#             */
/*   Updated: 2017/07/09 14:28:11 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H
#include "command_line.h"

/*
********************************************************************************
**                                     LEXER                                  **
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
	struct s_token	*n;
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
	IO_N,
	QUOTE,
	SPACE_TOK,
	WORD,
	FIL,
	DQUOTE,
	LOCAL
};

enum				e_dir
{
	RDIR = 22,
	BDIR,
	RRDIR,
	BBDIR,
	AGRE,
	BGRE
};

void				input(t_tok **cmd);
void				init_token(t_tok **lst);
void				tok_save(t_tok **lst, char **stack, int type);
void				flush(t_tok **lst, char **stack, char *line, int *i);
void				new_parser(t_tok **cmd, char *line);
void				quote(t_tok **lst, char **stack, char *line, int *i);
void 				bang(t_tok **lst, char **stack, char *line, int *i);
void				chevron(t_tok **lst, char **stack, char *line, int *i);
void				question_mark(t_tok **lst, char **stack, char *line, int *i);
void				pipe_pars(t_tok **lst, char **stack, char *line, int *i);
void				and_pars(t_tok **lst, char **stack, char *line, int *i);
int					arg_check(int ac, int i, char **av, char **envp);
int					io_number(char *str);
void				specified_dir(t_tok **lst);
int					is_space(char c);
int					check_end(char *line);
void				delete_lst(t_tok **cmd);
void				st_tok(char **stack, char c);
void				input(t_tok **cmd);
void				parser_line(char *line);
void				lexer_check(t_tok **lst);
int					fill_tmp(char tmp[], char c);
void				expanse(t_tok **lst, t_env **env);

#endif
