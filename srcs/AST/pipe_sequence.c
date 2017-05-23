/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 14:50:09 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/23 19:48:44 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"

t_tok	*find_pipe_tok(t_tok **lst, t_tok **stop)
{
	t_tok	*tmp;

	tmp = *lst;
	while (tmp && tmp != *stop && (tmp->type != PIPE))
		tmp = tmp->next;
	return (tmp);
}

void	check_pipe_sep(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_tok	*tmp_first;
	t_tok	*new_sep;
	t_ast	*tmp_ast;

	tmp_first = *lst;
	new_sep = NULL;
	tmp_ast = *ast;
	while ((tmp = find_pipe_tok(&tmp_first, sep)) != *sep)
	{
		new_sep = tmp;
		tmp_first = tmp->next;
		tmp = tmp->next;
	}
	if (new_sep)
	{
		init_ast(&tmp_ast->left, NULL, PIPE_SEQ);
		init_ast(&tmp_ast->left->right, NULL, CMD_SEQ);
		command_sequence(&tmp_ast->left->right, &tmp_first, &tmp);
		pipe_sequence(&tmp_ast->left, lst, sep);
	}
	else
	{
		init_ast(&tmp_ast->right, NULL, CMD_SEQ);
		command_sequence(&tmp_ast->right, lst, sep);
	}
}

void	pipe_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_tok	*tmp_first;
	t_tok	*new_sep;
	t_ast	*tmp_ast;

	tmp_ast = *ast;
	tmp_first = *lst;
	while ((tmp = find_pipe_tok(&tmp_first, sep)) != *sep)
	{
		tmp_first = tmp->next;
		new_sep = tmp;
		tmp = tmp->next;
	} // En faire une fonction
	if (tmp_first != *lst)
	{
		init_ast(&tmp_ast->left, new_sep->str, new_sep->type);
		tmp_ast = tmp_ast->left;
		init_ast(&tmp_ast->right, NULL, CMD_SEQ);
		command_sequence(&tmp_ast->right, &tmp_first, &tmp);
		pipe_sequence(&tmp_ast, lst, &new_sep);
	}
	else
	{
		init_ast(&tmp_ast->left, NULL, CMD_SEQ);
		command_sequence(&tmp_ast->left, lst, sep);
	}
} // Actually Work

int		exec_pipe_sequence(t_ast **ast, t_env **env)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp->left->type == PIPE)
	{
		if (exec_pipe_sequence(&tmp->left, env) == 1)
		{
			if (tmp->left->right->type == CMD_SEQ)
			{
				cmd_seq(&tmp->left->right, env); // IMPLEMENTATION IF exec_oa_sequence() == 0 ? Check rdir : cmd_seq();
				return (1);
			}
		}
		else
			ft_errormsg(NULL, NULL, "exec_oa_sequence returned 0");
	}
	else if (tmp->left->type == CMD_SEQ)
	{
		cmd_seq(&tmp->left, env);
		return (1);
	}
	return (0);
}
