/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 23:01:51 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/18 14:28:09 by zadrien          ###   ########.fr       */
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
		init_fork(&(*job)->pgid, 0);
		exec_fork(&p, n_env, -1);
	}
	else
	{
		fd_printf(2, "[%d] %d\n", (*job)->num, p->pid);
		(*job)->pgid = p->pid;
		if (kill(-p->pid, SIGCONT) < 0)
			fd_printf(2, "[%d] Done     %s\n", (*job)->num, (*job)->command);
		init_father(&p->pid, &(*job)->pgid, 0);
	}
	ft_freetab(n_env);
	return (p->status);
}

int		pipe_bg(t_process **process, pid_t *pgid, char **env, int r)
{
	t_process	*p;
	int			fd[2];

	p = *process;
	if (!pipe(fd))
	{
		if (!(p->pid = fork()))
		{
			close(fd[0]);
			init_fork(pgid, 0);
			p->next ? dup2(fd[1], STDOUT_FILENO) : 0;
			exec_fork(&p, env, r);
		}
		else
		{
			init_father(&p->pid, pgid, 0);
			cont_pipe_bg(&p, pgid, env, fd);
			if (kill(-p->pid, SIGCONT) < 0)
				;
		}
	}
	return (p->status);
}

int		cont_pipe_bg(t_process **pro, pid_t *pgid, char **env, int *fd)
{
	close(fd[1]);
	(*pro)->next ? pipe_bg(&(*pro)->next, pgid, env, fd[0]) : 0;
	close(fd[0]);
	return (1);
}
