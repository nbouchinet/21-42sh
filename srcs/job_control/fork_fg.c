/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_fg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 21:46:33 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/14 23:38:59 by zadrien          ###   ########.fr       */
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

int		cont_pipe_fg(t_process **lst, char **env, pid_t main, int *p)
{
	int		status;

	status = 0;
	close(p[1]);
	if ((*lst)->next)
		status = pipe_job_fg(&(*lst)->next, env, p[0], main);
	close(p[0]);
	return (status);
}

int		pipe_job_fg(t_process **lst, char **env, int r, pid_t main)
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
			active_sig(tmp->pid, main, 1);
			tmp->next != NULL ? dup2(p[1], STDOUT_FILENO) : 0;
			exec_fork(&tmp, env, r);
		}
		else
		{
			set_pgid(tmp->pid, &main, 1);
			tcsetpgrp(g_shell_terminal, tmp->pid);
			status = cont_pipe_bg(&tmp, env, main, p);
			waitpid(tmp->pid, &tmp->status, WUNTRACED | WCONTINUED);
		}
	}
	return (status != 0 ? status : tmp->status);
}


int		main_fork_fg(t_job **lst, char **env)
{
	int		status;
	int		ret;

	status = 0;
	(*lst)->bg = 0;
	if (!((*lst)->pgid = fork()))
	{
		active_sig(getpid(), getpid(), 1);
		ret = pipe_job_fg(&(*lst)->first_process, env, -1, (*lst)->pgid);
		if (!return_exec(ret))
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
	{
		set_pgid((*lst)->pgid, &(*lst)->pgid, 1);
		waitpid((*lst)->pgid, &status, WCONTINUED | WUNTRACED);
		(*lst)->status = status;
		catch_error(lst, (*lst)->status);
		tcsetpgrp(g_shell_terminal, g_shell_pgid);
	}
	return (status);
}
