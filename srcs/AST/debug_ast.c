/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 14:45:55 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/24 14:26:58 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

typedef struct		s_seq
{
	int				type;
	int			(*f)(t_ast**, t_env **);
}					t_seq;

void	exec_ast(t_ast **ast, t_env **env)
{
	int					i;
	t_ast				*tmp;
	static const t_seq	seq[3] = {{CMD_SEQ, & cmd_seq},
		{PIPE_SEQ, &exec_pipe_sequence}, {AND_OR, &exec_oa_sequence}};

	i = -1;
	tmp = *ast;
	while (tmp)
	{
		i = -1;
		while (++i < 3)
			if (seq[i].f(&tmp, env) == 1)
				continue ;
		tmp = tmp->right;
	}
}

int		cmd_seq(t_ast **ast, t_env **env)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp->type == PIPE_SEQ)
	{
		exec_pipe_sequence(&tmp, env);
	}
	else if (tmp->type == CMD_SEQ)
		if (exec_cmd_seq(&tmp->left, env) == 1)
			return (1);
	// if (tmp->right)
	// 	io_command(&tmp->right);
	return (0);
}

void	simple_command(t_ast **ast)
{
	t_ast	*tmp;

	tmp = *ast;
	ft_putendl("/// SIMP_CMD \\\\\\");
	ft_putendl("==branche de gauche==");
	ft_putendl(tmp->left->str);
	ft_putendl("==branche de droite==");
	tmp = tmp->right;
	while (tmp)
	{
		ft_putendl(tmp->str);
		tmp = tmp->right;
	}
}

int		exec_oa_sequence(t_ast **ast, t_env **env)
{
	t_ast	*tmp;

	tmp = *ast;
	if ((tmp->left->type == AND && exec_oa_sequence(&tmp->left, env)) ||
		(tmp->left->type == OR && !exec_oa_sequence(&tmp->left, env)))
	{
		if (tmp->left->right->type == CMD_SEQ || tmp->left->right->type == PIPE)
		{
			if (cmd_seq(&tmp->left->right, env) == 1) // IMPLEMENTATION IF exec_oa_sequence() == 0 ? Check rdir : cmd_seq();
				return (1);
		}
		// else
			// ft_errormsg(NULL, NULL, "exec_oa_sequence returned 0");
	}
	else if (tmp->left->type == CMD_SEQ || tmp->left->type == PIPE_SEQ)
		if (cmd_seq(&tmp->left, env) == 1)
			return (1);
	return (0);
}

void	simple_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_ast	*tmp_ast;

	tmp = *lst;
	tmp_ast = *ast;
	init_ast(&tmp_ast->left, tmp->str, CMD_NAME);
	tmp = tmp->next;
	while (tmp != *sep)
	{
		init_ast(&tmp_ast->right, tmp->str, CMD_ARG);
		if (tmp->next != *sep)
		tmp_ast = tmp_ast->right;
		tmp = tmp->next;
	}
}

void	command_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_ast	*tmp_ast;

	tmp = *lst;
	tmp_ast = *ast;
	while (tmp && (tmp->type == 9 || tmp->type == QUOTE))
		tmp = tmp->next;
	init_ast(&tmp_ast->left, NULL, SIMP_CMD);
	simple_sequence(&tmp_ast->left, lst, &tmp);
	if (tmp != *sep)
	{
		init_ast(&tmp_ast->right, NULL, IO_SEQ);
		// io_sequence(&tmp_ast->right, &tmp, sep); // recursive call
	}
}
