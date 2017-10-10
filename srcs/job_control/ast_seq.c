/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_seq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 22:08:41 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 15:26:44 by zadrien          ###   ########.fr       */
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
			return (job_ast(&tmp->left->right, env, foreground));
	}
	else if (tmp->left->type == CMD_SEQ)
		return (job_ast(&tmp->left, env, foreground));
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

int		job_bg_seq(t_ast **ast, t_env **env, int foreground)
{
	t_ast	*tmp;

	foreground = 0;
	tmp = (*ast)->type == BG_SEQ ? (*ast)->right : *ast;
	if (tmp->type == BGE)
	{
		job_ast(&tmp->left, env, foreground);
		if (tmp->right)
			job_bg_seq(&tmp->right, env, foreground);
	}
	else
		job_ast(&tmp, env, 1);
	return (1);
}

void	job_cont_bg(t_process **lst, char **env, t_job **job, int *p)
{
	close(p[1]);
	(*lst)->next ? exec_pipe_bg(&(*lst)->next, env, p[0], job) : 0;
	close(p[0]);
}
