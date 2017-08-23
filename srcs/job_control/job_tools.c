/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 16:25:42 by zadrien           #+#    #+#             */
/*   Updated: 2017/08/22 22:52:28 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_shell(void)
{
	g_shell_terminal = STDIN_FILENO;
	g_shell_is_interactive = isatty (g_shell_terminal);

	if (g_shell_is_interactive)
	{
		while (tcgetpgrp (g_shell_terminal) != (g_shell_pgid = getpgrp ()))
			kill (- g_shell_pgid, SIGTTIN);
		signal (SIGINT, SIG_IGN);
		signal (SIGQUIT, SIG_IGN);
		signal (SIGTSTP, SIG_IGN);
		signal (SIGTTIN, SIG_IGN);
		signal (SIGTTOU, SIG_IGN);
		signal (SIGCHLD, SIG_IGN);
		g_shell_pgid = getpid ();
		if (setpgid (g_shell_pgid, g_shell_pgid) < 0)
		{
			perror ("Couldn't put the shell in its own process group");
			exit (1);
		}
		tcsetpgrp (g_shell_terminal, g_shell_pgid);
		tcgetattr (g_shell_terminal, &g_shell_tmodes);
	}
}

int		job_is_stopped(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed && !p->stopped)
			return (0);
		p = p->next;
	}
	return (1);
}

int		job_is_complete(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed)
			return (0);
		p = p->next;
	}
	return (1);
}

void	mark_job_status(t_job **job, int status, pid_t pid)
{
	t_process	*p;

	p = (*job)->first_process;
	ft_putendl("In");
	// sleep(30);
	while (p)
	{
		if (p->pid == pid)
		{
			if (WIFSTOPPED(status))
				p->stopped = 1;
			else if (WIFEXITED(status))
				p->completed = 1;
			break ;
		}
		p = p->next;
	}
}

int		mark_process_status(t_job **job)
{
	t_process	*p;

	if (*job)
	{
		p = (*job)->first_process;
		while (p)
		{
			if (WIFSTOPPED(p->status))
				p->stopped = 1;
			else
			{
				p->completed = 1;
				if (WIFSIGNALED(p->status))
				{
					ft_putnbrl(p->pid);
					ft_errormsg("21sh:", "Child process", "killed by signal");
				}
			}
			p = p->next;
		}
		return (0);
	}
	else
		return (ft_errormsg("21sh:", NULL, "Job doesn't exist"));
}
