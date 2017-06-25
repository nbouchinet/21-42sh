/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:32:03 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/04 16:25:37 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_H
# define LEXER_PARSER_H

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
	IO_N,
	QUOTE,
	SPACE_TOK,
	WORD,
	FILENAME
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
void				lexer_check(t_tok **lst);
// void				delete_lstenv(t_env **cmd);
void 				specified_dir(t_tok **lst);
void				destroy_tok(t_tok **head);
int					fill_tmp(char tmp[], char c);

#endif
