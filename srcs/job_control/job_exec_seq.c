/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:18:09 by nbouchin          #+#    #+#             */
/*   Updated: 2017/09/25 12:19:49 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		job_qm_seq(t_ast **ast, t_env **env, int foreground)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp->left->type == QM)
	{
		if (job_qm_seq(&tmp->left, env, foreground) == 1)
			job_ast(&tmp->left->right, env, foreground);
	}
	else if (tmp->left->type == CMD_SEQ)
		job_ast(&tmp->left, env, foreground);
	return (1);
}

int		job_oa_seq(t_ast **ast, t_env **env, int foreground)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp->type == OR)
	{
		if (job_oa_seq(&tmp->left, env, foreground) == 0)
			return (job_oa_seq(&tmp->right, env, foreground));
		return (1);
	}
	else if (tmp->type == AND)
	{
		if (job_oa_seq(&tmp->left, env, foreground) == 1)
			return (job_oa_seq(&tmp->right, env, foreground));
	}
	else if (tmp && tmp->type == PIPE_SEQ)
		return (job_pipe(&tmp, env, foreground));
	else if (tmp && tmp->type == CMD_SEQ)
		return (job_cmd_seq(&tmp, env, foreground));
	return (0);
}

int		job_andor(t_ast **ast, t_env **env, int foreground)
{
	return (job_oa_seq(&(*ast)->left, env, foreground));
}

void	print_process(t_process **pro)
{
	int			i;
	t_process	*tmp;

	tmp = *pro;
	i = -1;
	while (tmp->argv[++i])
		printf("%s\n", tmp->argv[i]);
}
