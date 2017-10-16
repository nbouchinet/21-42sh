/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_fg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 21:46:33 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/16 19:31:45 by zadrien          ###   ########.fr       */
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

int		pipe_fg(t_process **process, pid_t *pgid, char **env, int r)
{
	t_process *p;
	int			fd[2];
	p = *process;
	if (!pipe(fd))
	{
		if (!(p->pid = fork()))
		{
			close(fd[0]);
			init_fork(pgid, 1);
			p->next ? dup2(fd[1], STDOUT_FILENO) : 0;
			exec_fork(&p, env, r);
		}
		else
		{
			init_father(&p->pid, pgid, 1);
			cont_pipe_fg(&p, pgid, env, fd);
			waitpid(p->pid, &p->status, WCONTINUED | WUNTRACED);
		}
	}
	return (p->status);
}

int		cont_pipe_fg(t_process **pro, pid_t *pgid, char **env, int *fd)
{
	close(fd[1]);
	(*pro)->next ? pipe_fg(&(*pro)->next, pgid, env, fd[0]) : 0;
	close(fd[0]);
	return (1);
}
