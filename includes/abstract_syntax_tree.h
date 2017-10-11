/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_syntax_tree.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:29:51 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/11 10:58:09 by nbouchin         ###   ########.fr       */
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
	CMD_SEQ = 43,
	PIPE_SEQ = 44,
	BG_SEQ = 45,
	AND_OR = 46,
	IO_FILE = 47,
	CMD_NAME_ABS = 48,
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
t_tok				*valid_arg(t_tok **lst, t_ast **ast, t_tok **sep);
t_tok				*stock_local(t_tok **lst, t_tok **sep, int i);

#endif
