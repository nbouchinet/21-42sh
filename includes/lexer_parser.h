/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:32:03 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 14:49:48 by zadrien          ###   ########.fr       */
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

# define NE 1
# define CURR 2

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
void				new_parser(t_tok **cmd, char *line, int i);
void				flush(t_tok **lst, char **stack, char *line, int *i);
void				tok_save(t_tok **lst, char **stack, int type);
void				ft_quote(t_tok **lst, char **stack, char *line, int *i);
void				chevron(t_tok **lst, char **stack, char *line, int *i);
void				question_mark(t_tok **lst, char **stack, char *line,
					int *i);
void				pipe_pars(t_tok **lst, char **stack, char *line, int *i);
void				and_pars(t_tok **lst, char **stack, char *line, int *i);
void				backslash(t_tok **lst, char **stack, char *line, int *i);
int					is_sep(char c);
void				st_tok(char **stack, char c, int reset);
int					io_number(char *str);
int					is_space(char c);
int					check_end(char *line);
t_local				*find_local(t_local **local, char *var);
void				tild(t_tok **lst, char **stack, char *line, int *i);
void				lexer_exp(t_tok **lst, char **stack, char *line, int *i);
void				complete_st_quote(char **stack, char **ins, char **str);
void				stuck_quote(char **stack, char *line, int *i);
void				complete(char **stack, char *line, int *i);
int					print_error_lexer(t_tok **lst, t_tok **n, int mod);
void				replace_tok(t_tok **start, t_tok **next, t_tok **sub,
					t_tok **sub_end);
void				swap_tok(t_tok **lst, t_tok **start, t_tok **next,
					t_tok **w);
int					error_lexer(t_tok **p, t_tok **tmp, t_tok **n);
int					new_lexercheck(t_tok **lst);
void				specified_dir(t_tok **lst);
void				check_rdir(t_tok **lst, t_tok **start, t_tok **next);
void				restruct_lst(t_tok **lst);
void				init_token(t_tok **lst);
void				tok_save(t_tok **lst, char **stack, int type);
void				find_var(char *var, char **stack);
void				expanse_stack(char **stack, char *line, int *i);
void				in_quote(char **stack, char *line, int *i, char type);
void				after_quote(char **stack, char *line, int *i);
int					heredoc(t_tok **lst, t_tok *prev);
void				creat_file(t_tok **lst);
int					hd_loop(t_tok **stop, t_cmdl *cmdl, int p[2], int ret);
int					next_hd(t_tok **tok);
int					hd_signal(t_cmdl *cmdl);
#endif
