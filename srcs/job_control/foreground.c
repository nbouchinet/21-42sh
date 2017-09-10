/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:48:35 by nbouchin          #+#    #+#             */
/*   Updated: 2017/09/10 17:53:22 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		sus_pid(t_job **job, t_ast **ast, t_job **table)
{
	int			nbjob;
	t_job		*head;
	t_process	*phead;

	(void)job;
	(void)ast;
	nbjob = 1;
	if (!(*table))
		return (0);
	head = (*table);
	phead = (*table)->first_process;
	while ((*table)->next)
	{
		(*table) = (*table)->next;
		nbjob++;
	}
	if ((*table)->first_process->stopped != 1)
	{
		phead = (*table)->first_process;
		printf("[%d]+  Stopped			%s\n", nbjob, (*table)->command);
		kill((*table)->pgid, SIGTSTP);
		(*table)->first_process = phead;
	}
	(*table) = head;
	return (1);
}

void            catch_error(t_job **job, int status)
{
	if (WTERMSIG(status) == SIGSEGV)
		fd_printf(3, "Segmentation fault: 11\n");
	else if (WTERMSIG(status) == SIGABRT)
		fd_printf(3, "Abort trap: 6\n");
	else if (WTERMSIG(status) == SIGBUS)
		fd_printf(3, "Bus error: 10\n");
	else if (WSTOPSIG(status) == SIGTSTP)
		fd_printf(3, "[%d]+  Stopped    %s\n", 1, (*job)->command);
}

void	wait_for_job(t_job **job)
{
	pid_t		pid;
	int			status;

	while (!job_is_stopped(*job) && !job_is_complete(*job))
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WCONTINUED);
		if (mark_job_status(job, status, pid) == 0)
			break ;
	}
}

void	mark_job_as_running(t_job **job)
{
	t_process	*p;

	p = (*job)->first_process;
	while (p)
	{
		p->stopped = 0;
		p = p->next;
	}
}

int		background(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;
	(void)job;
	(void)ast;

	if (*table)
	{
		j = *table;
		while (j->next)
			j = j->next;
		if (j)
		{
			mark_job_as_running(&j);
			if (kill (- j->pgid, SIGCONT) < 0)
				perror ("kill (SIGCONT)");
			// tcsetpgrp(g_shell_terminal, j->pgid);
			// wait_for_job(&j);
			tcsetpgrp (g_shell_terminal, g_shell_pgid);
		}
		return (1);
	}
	return (0);
}

int		foreground(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;
	(void)job;
	(void)ast;

	if (*table)
	{
		j = *table;
		while (j->next)
			j = j->next;
		if (j)
		{
			mark_job_as_running(&j);
			if (kill (- j->pgid, SIGCONT) < 0)
				perror ("kill (SIGCONT)");
			tcsetpgrp(g_shell_terminal, j->pgid);
			wait_for_job(&j);
			tcsetpgrp (g_shell_terminal, g_shell_pgid);
		}
		return (1);
	}
	return (0);
}
