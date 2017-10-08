/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 21:46:33 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/08 11:40:24 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			exec_pro(t_process **lst, t_env **env, t_job **j)
{
	char		**n_env;
	t_process	*tmp;

	tmp = *lst;
	n_env = get_env(env, tmp->argv[0]);
	if (!(tmp->pid = fork()))
	{
		g_shell_is_interactive ? active_sig(tmp->pid, (*j)->pgid, 1) : 0;
		if (tmp->rdir)
			if (!io_seq(&tmp->rdir))
				exit(EXIT_FAILURE);
		execve(tmp->argv[0], tmp->argv, n_env);
		exit(EXIT_SUCCESS);
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
			tmp->next != NULL ? dup2(p[1], STDOUT_FILENO) : 0;
			r != -1 ? dup2(r, STDIN_FILENO) : 0;
			if (tmp->rdir && !io_seq(&tmp->rdir))
					exit(EXIT_FAILURE);
			active_sig(tmp->pid, (*job)->pgid, 1);
			if (tmp->builtin && !pipe_builtin(&tmp->builtin, &tmp->env, 1))
				exit(EXIT_FAILURE);
			else if (!tmp->builtin)
				execve(tmp->argv[0], tmp->argv, env);
			exit(EXIT_SUCCESS);
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
			r != -1 ? dup2(r, STDIN_FILENO) : 0;
			if (tmp->rdir && !io_seq(&tmp->rdir))
				exit(EXIT_FAILURE);
			if (tmp->builtin && !pipe_builtin(&tmp->builtin, &tmp->env, 1))
				exit(EXIT_FAILURE);
			else if (!tmp->builtin)
				execve(tmp->argv[0], tmp->argv, env);
			execve(tmp->argv[0], tmp->argv, env);
		}
		else
		{
			set_pgid(tmp->pid, &(*job)->pgid, 0);
			job_cont_bg(&tmp, env, job, p);
			if (kill(-tmp->pid, SIGCONT) < 0)
				perror("kill (SIGCONT)");
			return (tmp->status);
		}
	}
	return (0);
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
		if (p->rdir && !io_seq(&p->rdir))
				exit(EXIT_FAILURE);
		execve(p->argv[0], p->argv, n_env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		fd_printf(2, "[%d] %d\n", (*job)->num, p->pid);
		fd_printf(2, "[%d] Done     %s\n", (*job)->num, (*job)->command);
		set_pid(p->pid, &(*job)->pgid, 0);
		if (kill(-(*job)->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)");
	}
	ft_freetab(n_env);
	return (p->status);
}
