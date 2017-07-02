/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_seq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 10:22:09 by zadrien           #+#    #+#             */
/*   Updated: 2017/07/02 16:17:51 by zadrien          ###   ########.fr       */
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
	int		i;
	t_ast	*tmp;

	i = 0;
	tmp = *ast;
	if ((tmp->left->type == AND && exec_oa(&tmp->left, env, type) == 1) ||
	(tmp->left->type == OR && (i = exec_oa(&tmp->left, env, type))))
	{
		if (i == 1)
			return (1);
		if (exec_cmd_seq(&tmp->left->right, env, tmp->left->right->type) == 1)
			return (1);
	}
	else
	{
		if (tmp->left->type == CMD_SEQ)
			if (exec_cmd_seq(&tmp->left, env, tmp->left->type) == 1)
				return (1);
	}
	return (0);
}
