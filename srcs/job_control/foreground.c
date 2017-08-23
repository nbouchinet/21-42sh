/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:48:35 by nbouchin          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2017/08/22 17:58:36 by nbouchin         ###   ########.fr       */
=======
/*   Updated: 2017/08/22 22:49:57 by zadrien          ###   ########.fr       */
>>>>>>> 0a08fd6c1c7f3c39df8774549ac5aef5c91c7464
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int		sus_pid(t_job **job, t_ast **ast, t_job **table)
{
	int			i;
	t_job		*j;
	t_process	*p;

	(void)job;
	(void)ast;
	if (*table)
	{
		i = 1;
		j = *table;
		while (j && !(j->first_process->stopped != 1 && j->first_process->completed != 1))
		{
			j = j->next;
			i++;
		}
		p = j->first_process;
		ft_printf("[%d]+  Stopped			%s\n", i, j->command);
		while (p)
		{
			p->stopped = 1;
			kill(p->pid, SIGTSTP);
			p = p->next;
		}
	}
	return (1);
}
// int		sus_pid(t_job **job, t_ast **ast, t_job **table)
// {
// 	int			nbjob;
// 	t_job		*head;
// 	t_process	*phead;
//
// 	(void)job;
// 	(void)ast;
// 	nbjob = 1;
// 	if (!(*table))
// 		return (0);
// 	head = (*table);
// 	phead = (*table)->first_process;
// 	while ((*table)->next)
// 	{
// 		(*table) = (*table)->next;
// 		nbjob++;
// 	}
// 	if ((*table)->first_process->stopped != 1)
// 	{
// 		phead = (*table)->first_process;
// 		printf("[%d]+  Stopped			%s\n", nbjob, (*table)->command);
// 		while ((*table)->first_process)
// 		{
// 			(*table)->first_process->stopped = 1;
// 			kill((*table)->first_process->pid, SIGTSTP);
// 			(*table)->first_process = (*table)->first_process->next;
// 		}
// 		(*table)->first_process = phead;
// 	}
// 	(*table) = head;
// 	return (1);
// }

void	wait_for_job(t_job **job)
{
	pid_t		pid;
	int			status;

	while (!job_is_stopped(*job) && !job_is_complete(*job))
	{
		ft_putendl("A");
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
	if (*table)
	{
		j = *table;
		// tcsetpgrp (g_shell_terminal, j->pgid);
		while (j->next)
			j = j->next;
		p = j->first_process;
		mark_job_as_running(&j);
		print_job(&j);
		// sleep(10);
		if (kill (- j->pgid, SIGCONT) < 0)
			perror ("kill (SIGCONT)");
		// tcsetattr (g_shemll_terminal, TCSADRAIN, &j->tmodes);
		while (p)
		{
			kill(p->pid, SIGCONT);
			p = p->next;
		}
		wait_for_job(&j);
		/* Restore the shell’s terminal modes.  */
		// ft_putnbrl(g_shell_pgid);
		// init_shell();
		// tcgetattr (g_shell_terminal, &j->tmodes);
		// tcsetattr (g_shell_terminal, TCSADRAIN, &g_shell_tmodes);
		return (1);
	}
	return (0);
}
