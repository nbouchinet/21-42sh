/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:48:35 by nbouchin          #+#    #+#             */
/*   Updated: 2017/09/14 18:33:39 by zadrien          ###   ########.fr       */
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

void	wait_for_job(t_job **job)
{
	pid_t		pid;
	int			status;

	status = 0;
	while (!job_is_stopped(*job) && !job_is_complete(*job))
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WCONTINUED);
		catch_error(job, status);
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

int		find_pgid(t_job **table, char *str)
{
	t_job	*j;
	int		i;
	j = *table;
	i = ft_atoi(str);
	while (j->next)
	{
		if (str && j->pgid == i)
			return (j->pgid);
		else
		j = j->next;
	}
	if (j->pgid == i)
		return (j->pgid);
	return (-1);
}

int		background(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;
	int			pgid;

	(void)ast;
	(void)job;
	pgid = 0;
	if (*table)
	{
		j = *table;
		if (j)
		{
			if (pgid = find_pgid(table, (*ast)->right->left ? (*ast)->left->right->str : NULL));
			mark_job_as_running(&j);
			if (kill(-j->pgid, SIGCONT) < 0)
				perror("kill (SIGCONT)");
			tcsetpgrp(g_shell_terminal, g_shell_pgid);
		}
		return (1);
	}
	return (0);
}


int			foreground(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;
	int			nf;

	(void)job;
	(void)ast;
	nf = 0;
	if (*table)
	{
		j = *table;
		if ((*ast)->left->right)
		{
			while (j)
			{
				if (j->pgid == ft_atoi((*ast)->left->right->str))
				{
					nf = 1;
					break ;
				}
				else
					j = j->next;
			}
			if (nf == 0)
			{
				fd_printf(2, "42sh: fg: %s: no such job\n",
				(*ast)->left->right->str);
				return (0);
			}
		}
		else
			while (j->next)
				j = j->next;
		if (j)
		{
			mark_job_as_running(&j);
			if (kill(-j->pgid, SIGCONT) < 0)
				perror("kill (SIGCONT)");
			tcsetpgrp(g_shell_terminal, j->pgid);
			wait_for_job(&j);
			tcsetpgrp(g_shell_terminal, g_shell_pgid);
		}
		return (1);
	}
	if ((*ast)->left->right)
		fd_printf(2, "42sh: fg: %s: no such job\n", (*ast)->left->right->str);
	else
		ft_putendl_fd("42sh: fg: current: no such job", 2);
	return (0);
}
