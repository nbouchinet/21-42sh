/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_syntax_tree.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:24:36 by nbouchin          #+#    #+#             */
/*   Updated: 2017/09/17 18:13:00 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_SYNTAX_TREE_H
# define ABSTRACT_SYNTAX_TREE_H

/*
******************************************************
**               Abstract Syntax Tree               **
******************************************************
*/

enum				e_ast
{
	QM_SEQ = 42,
	CMD_SEQ,
	PIPE_SEQ,
	BG_SEQ,
	AND_OR,
	IO_FILE,
	CMD_NAME_ABS,
	SIMP_CMD,
	CMD_ARG,
	IO_SEQ,
	CMD_NAME_RLT
};

typedef struct		s_ast
{
	char			*str;
	int				type;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

void				init_ast(t_ast **ast, t_tok **tok, int type);
void				primary_sequence(t_ast **ast, t_tok **lst);
void				secondary_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
void				tertiary_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
void				quaternary_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
void				qm_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
void				oa_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
void				bg_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
void				pipe_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
void				command_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
void				io_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
void				simple_sequence(t_ast **ast, t_tok **lst, t_tok **sep);
t_tok				*find_q_tok(t_tok **lst);
t_tok				*find_qm_tok(t_tok **lst, t_tok **stop);
t_tok				*multi_qm(t_tok **lst);
void				ft_putast(t_ast *root);
void				destroy_ast(t_ast **head);
void				destroy_tok(t_tok **head);

#endif
