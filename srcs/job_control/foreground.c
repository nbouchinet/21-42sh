/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:48:35 by nbouchin          #+#    #+#             */
//   Updated: 2017/09/04 13:08:37 by nbouchin         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


// int		sus_pid(t_job **job, t_ast **ast, t_job **table)
// {
// 	int			i;
// 	t_job		*j;
//
// 	(void)job;
// 	(void)ast;
// 	if (*table)
// 	{
// 		i = 1;
// 		j = *table;
// 		if (j)
// 		{
// 			while (j && !(j->first_process->stopped != 1 && j->first_process->completed != 1))
// 			{
// 				j = j->next;
// 				i++;
// 			} // Condition a revoir
// 			if (j)
// 			{
// 				ft_putendl_fd(j->command, 2);
// 				mark_job_as_stopped(&j);
// 				if (kill(j->pgid, SIGTSTP))
// 					;
// 			}
// 		}
// 	}
// 	return (1);
// }
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

void	wait_for_job(t_job **job)
{
	pid_t		pid;
	int			status;

	status = 0;
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

int		foreground(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;
	t_process	*p;
	(void)job;
	(void)ast;

	if (*table)
	{
		j = *table;
		while (j->next)
			j = j->next;
		p = j->first_process;
		mark_job_as_running(&j);
		tcsetpgrp (g_shell_terminal, j->pgid);
		if (kill (- j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
		wait_for_job(&j);
		tcsetpgrp (g_shell_terminal, g_shell_pgid);
		return (1);
	}
	return (0);
}
