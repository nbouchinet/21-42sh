/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_bg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 23:57:24 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/01 23:58:40 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		job_bg_seq(t_ast **ast, t_env **env, int foreground)
{
	t_ast	*tmp;

	foreground = 0;
	tmp = (*ast)->type == BG_SEQ ? (*ast)->right : *ast;
	if (tmp->type == BG)
	{
		job_ast(&tmp->left, env, foreground);
		if (tmp->right)
			job_bg_seq(&tmp->right, env, foreground);
	}
	else
		job_ast(&tmp, env, 1);
	return (1);
}

int		exec_bg_seq(t_ast **ast, t_env **env)
{
	t_job	*job;
	t_ast	*tmp;

	tmp = *ast;
	if (init_job(&job) == 1)
	{
		job->command = init_job_name(ast);
		if (!init_process(ast, &job->first_process, env))
			return (-1);
		return (exec_job_bg(&job, env));
	}
	return (-1);
}

int		exec_job_bg(t_job **job, t_env **env)
{
	int		status;

	job_control(job, NULL, ADD);
	status = exec_pro_bg(&(*job)->first_process, env, job);
	if (job_is_stopped(*job))
		return (1);
	return (0);
}

void	job_cont_bg(t_process **lst, char **env, t_job **job, int *p)
{
	close(p[1]);
	(*lst)->next ? exec_pipe_bg(&(*lst)->next, env, p[0], job) : 0;
	close(p[0]);
}
