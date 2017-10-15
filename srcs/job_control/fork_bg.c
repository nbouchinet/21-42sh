/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 23:01:51 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/15 14:47:19 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
		if (kill (- p->pid, SIGCONT) < 0)
			fd_printf(2, "[%d] Done     %s\n", (*job)->num, (*job)->command);
			// fd_printf(2, "[%d] Done     \n", 0);
		set_pid(p->pid, &(*job)->pgid, 0);
	}
	ft_freetab(n_env);
	return (p->status);
}

int		cont_pipe_bg(t_process **lst, char **env, pid_t main, int *p)
{
	int		status;

	status = 0;
	close(p[1]);
	if ((*lst)->next)
		status = pipe_job_bg(&(*lst)->next, env, p[0], main);
	close(p[0]);
	return (status);
}

int		pipe_job_bg(t_process **lst, char **env, int r, pid_t main)
{
	int			p[2];
	int			status;
	t_process	*tmp;

	status = 0;
	tmp = *lst;
	main == 0 ? main = getpid() : 0;
	if (pipe(p) == 0)
	{
		if ((tmp->pid = fork()) == 0)
		{
			close(p[0]);
			active_sig(tmp->pid, main, 0);
			tmp->next != NULL ? dup2(p[1], STDOUT_FILENO) : 0;
			exec_fork(&tmp, env, r);
		}
		else
		{
			set_pgid(tmp->pid, &main, 0);
			status = cont_pipe_bg(&tmp, env, main, p);
		}
	}
	return (status != 0 ? status : tmp->status);
}


int		main_fork_bg(t_job **lst, char **env)
{
	int		status;
	int		ret;

	status = 0;
	if (!((*lst)->pgid = fork()))
	{
		active_sig(getpid(), getpid(), 0);
		ret = pipe_job_bg(&(*lst)->first_process, env, -1, (*lst)->pgid);
		waitpid((*lst)->first_process->pid, &status, WUNTRACED);
		if (!return_exec(status))
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
	{
		fd_printf(2, "[%d] %d\n", (*lst)->num, (*lst)->pgid);
		set_pgid((*lst)->pgid, &(*lst)->pgid, 0);
		if (kill (-(*lst)->pgid, SIGCONT) < 0)
			fd_printf(2, "[%d] Done     %s\n", (*lst)->num, (*lst)->command);
	}
	return (status);
}
