/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:29:51 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/24 13:47:24 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

/*
******************************************************
**               Abstract Syntax Tree              **
****************************************************
*/

enum 			e_ast
{
	QM_SEQ = 42,
	CMD_SEQ,
	PIPE_SEQ,
	AND_OR,
	IO_FILE,
	CMD_NAME,
	SIMP_CMD,
	CMD_ARG,
	IO_SEQ
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
void	qm_sequence(t_ast **ast, t_tok **lst, t_tok **sep);

#endif
