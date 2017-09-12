/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_seq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 10:22:09 by zadrien           #+#    #+#             */
/*   Updated: 2017/07/16 19:40:27 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		qm_seq(t_ast **ast, t_env **env, int type)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp->left->type == QM)
	{
		if (qm_seq(&tmp->left, env, type) == 1)
			exec_ast(&tmp->left->right, env);
	}
	else
		exec_ast(&tmp->left, env);
	return (1);
}

int		exec_oa(t_ast **ast, t_env **env, int type)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp->left->type == OR)
	{
		if (exec_oa(&tmp->left, env, type) == 0)
			return (exec_cmd_seq(&tmp->left->right, env,
				tmp->left->right->type));
		return (1);
	}
	else if (tmp->left->type == AND)
	{
		if (exec_oa(&tmp->left, env, type) == 1)
			return (exec_cmd_seq(&tmp->left->right, env,
				tmp->left->right->type));
	}
	else if (tmp->left->type == PIPE_SEQ)
		return (exec_cmd_seq(&tmp->left, env, PIPE_SEQ));
	else if (tmp->left->type == CMD_SEQ)
		return (exec_cmd_seq(&tmp->left, env, CMD_SEQ));
	return (0);
}
