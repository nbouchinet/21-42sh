/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 21:46:33 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 14:06:10 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		exec_pro(t_process **lst, t_env **env, t_job **j)
{
	char		**n_env;
	t_process	*tmp;

	tmp = *lst;
	n_env = get_env(env, tmp->argv[0]);
	if (!(tmp->pid = fork()))
	{
		active_sig(tmp->pid, (*j)->pgid, 1);
		exec_fork(&tmp, n_env, -1);
	}
	else
	{
		set_pid(tmp->pid, &(*j)->pgid, 1);
		waitpid(tmp->pid, &tmp->status, WCONTINUED | WUNTRACED);
		tcsetpgrp(g_shell_terminal, g_shell_pgid);
	}
	ft_freetab(n_env);
	return (tmp->status);
}

int		exec_pipe_job(t_process **lst, char **env, int r, t_job **job)
{
	int			p[2];
	int			status;
	t_process	*tmp;

	tmp = *lst;
	status = 0;
	if (pipe(p) == 0)
	{
		if ((tmp->pid = fork()) == 0)
		{
			close(p[0]);
			active_sig(tmp->pid, (*job)->pgid, 1);
			tmp->next != NULL ? dup2(p[1], STDOUT_FILENO) : 0;
			exec_fork(&tmp, env, r);
		}
		else
		{
			set_pgid(tmp->pid, &(*job)->pgid, 1);
			status = job_cont_pipe(&tmp, env, job, p);
			waitpid(tmp->pid, &tmp->status, WUNTRACED | WCONTINUED);
			catch_error(job, tmp->status);
			tcsetpgrp(g_shell_terminal, g_shell_pgid);
		}
	}
	return (tmp->status);
}

int		exec_pipe_bg(t_process **pro, char **env, int r, t_job **job)
{
	int			p[2];
	t_process	*tmp;

	tmp = *pro;
	if (pipe(p) == 0)
	{
		if (!(tmp->pid = fork()))
		{
			close(p[0]);
			active_sig(tmp->pid, (*job)->pgid, 0);
			tmp->next != NULL ? dup2(p[1], STDOUT_FILENO) : 0;
			exec_fork(&tmp, env, r);
		}
		else
		{
			set_pgid(tmp->pid, &(*job)->pgid, 0);
			job_cont_bg(&tmp, env, job, p);
		}
	}
	return (tmp->status);
}

int		exec_pro_bg(t_process **pro, t_env **env, t_job **job)
{
	char		**n_env;
	t_process	*p;

	p = *pro;
	n_env = get_env(env, p->argv[0]);
	if (!(p->pid = fork()))
	{
		active_sig(p->pid, (*job)->pgid, 0);
		exec_fork(&p, n_env, -1);
	}
	else
	{
		fd_printf(2, "[%d] %d\n", (*job)->num, p->pid);
		(*job)->pgid = p->pid;
		fd_printf(2, "[%d] Done     %s\n", (*job)->num, (*job)->command);
		set_pid(p->pid, &(*job)->pgid, 0);
	}
	ft_freetab(n_env);
	return (p->status);
}
