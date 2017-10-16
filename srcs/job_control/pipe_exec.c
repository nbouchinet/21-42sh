/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 22:23:48 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/16 20:56:58 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		job_pipe(t_ast **ast, t_env **env, int fg)
{
	t_job	*job;
	t_job	*tmp;

	if (init_job(&job) == 1)
	{
		tmp = job;
		tmp->command = init_pipe_job(ast);
		if (complete_process(&(*ast)->right, &tmp->first_process, env) == 1)
		{
			job_control(&job, NULL, ADD);
			return (pipe_job(&job, env, fg));
		}
		delete_job(&job);
	}
	return (0);
}

int		pipe_job(t_job **lst, t_env **env, int fg)
{
	int		status;
	char	**n_env;
	t_job	*tmp;

	tmp = *lst;
	status = 0;
	n_env = get_env(env, tmp->first_process->argv ?
						tmp->first_process->argv[0] : NULL);
	if (fg)
	{
		status = pipe_fg(&tmp->first_process, &tmp->pgid, n_env, -1);
		tcsetpgrp(g_shell_terminal, g_shell_pgid);
		mark_process_status(lst);
	}
	else
		status = pipe_bg(&tmp->first_process, &tmp->pgid, n_env, -1);
	ft_freetab(n_env);
	if (return_exec(status))
		return (1);
	return (0);
}
