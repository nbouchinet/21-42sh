/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:48:35 by nbouchin          #+#    #+#             */
/*   Updated: 2017/08/22 16:39:55 by zadrien          ###   ########.fr       */
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
		while ((*table)->first_process)
		{
			kill((*table)->first_process->pid, SIGTSTP);
			(*table)->first_process->stopped = 1;
			(*table)->first_process = (*table)->first_process->next;
		}
		(*table)->first_process = phead;
	}
	(*table) = head;
	return (1);
}

void	wait_for_job(t_job **job)
{
	t_process	*p;
	pid_t		pid;
	int			status;

	p = (*job)->first_process;
	if (!job_is_stopped(*job) && !job_is_complete(*job))
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WCONTINUED);
		mark_job_status(job, status, pid);
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

int		foreground(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;
	t_process	*p;
	(void)job;
	(void)ast;

	ft_putendl("WTF");
	j = *table;
	tcsetpgrp (g_shell_terminal, j->pgid);
	while (j->next)
	{
		j = j->next;
		ft_putendl("BOUCLE");
	}
	p = j->first_process;
	mark_job_as_running(&j);
	// sleep(30);
	while (p)
	{
		tcsetattr (g_shell_terminal, TCSADRAIN, &j->tmodes);
		kill(p->pid, SIGCONT);
		p = p->next;
	}
	wait_for_job(&j);
	/* Restore the shell’s terminal modes.  */
	tcsetpgrp (g_shell_terminal, g_shell_pgid);
	tcgetattr (g_shell_terminal, &j->tmodes);
	tcsetattr (g_shell_terminal, TCSADRAIN, &g_shell_tmodes);
	return (1);
}
