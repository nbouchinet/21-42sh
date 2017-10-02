/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 22:23:48 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/01 23:55:33 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		job_pipe(t_ast **ast, t_env **env, int foreground)
{
	t_job	*job;
	t_job	*tmp;

	if (init_job(&job) == 1)
	{
		tmp = job;
		tmp->command = init_pipe_job(ast);
		if (complete_process(&(*ast)->right, &tmp->first_process, env) == 1)
		{
			return (pipe_job(&job, env, foreground));
		}
		delete_job(&job);
	}
	return (0);
}

int		pipe_job(t_job **lst, t_env **env, int foreground)
{
	int		status;
	char	**n_env;
	t_job	*tmp;

	tmp = *lst;
	job_control(lst, NULL, ADD);
	n_env = get_env(env, tmp->first_process->argv ? tmp->first_process->argv[0] : NULL);
	if (foreground)
	{
		status = exec_pipe_job(&tmp->first_process, n_env, -1, lst);
		mark_process_status(lst);
	}
	else
		status = exec_pipe_bg(&tmp->first_process, n_env, -1, lst);
	ft_freetab(n_env);
	if (WIFEXITED(status) && !WEXITSTATUS(status))
		return (1);
	return (0);
}

void	job_cont_pipe(t_process **lst, char **env, t_job **job, int *p)
{
	close(p[1]);
	(*lst)->next != NULL ? exec_pipe_job(&(*lst)->next, env, p[0], job) : 0;
	close(p[0]);
}
