/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:48:35 by nbouchin          #+#    #+#             */
/*   Updated: 2017/09/14 21:54:03 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		sus_pid(t_job **job, t_ast **ast, t_job **table)
{
	(void)job;
	(void)ast;
	(void)table;
	/* int			nbjob; */
	/* t_job		*head; */
	/* t_process	*phead; */

	/* (void)job; */
	/* (void)ast; */
	/* nbjob = 1; */
	/* if (!(*table)) */
	/* 	return (0); */
	/* head = (*table); */
	/* phead = (*table)->first_process; */
	/* while ((*table)->next) */
	/* { */
	/* 	(*table) = (*table)->next; */
	/* 	nbjob++; */
	/* } */
	/* if ((*table)->first_process->stopped != 1) */
	/* { */
	/* 	phead = (*table)->first_process; */
	/* 	kill((*table)->pgid, SIGTSTP); */
	/* 	(*table)->first_process = phead; */
	/* } */
	/* (*table) = head; */
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

t_job	*find_pgid(t_job **table, t_ast **ast)
{
	t_job	*j;
	int		i;

	j = *table;
	if ((*ast) && (*ast)->left->right)
	{
		i = ft_atoi((*ast)->left->right->str);
		while (j)
		{
			if (j->pgid == i)
				return (j);
			j = j->next;
		}
	}
	else
	{
		while (j->next)
			j = j->next;
		return (j);
	}
	return (NULL);
}

int		background(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;

	(void)job;
	if (*table)
	{
		j = *table;
		if (j)
		{
			if ((j = find_pgid(table, ast)))
			{
				mark_job_as_running(&j);
				if (kill(- j->pgid, SIGCONT) < 0)
					perror("kill (SIGCONT)");
				tcsetpgrp(g_shell_terminal, g_shell_pgid);
			}
			else
				ft_errormsg("42sh: bg: ", (*ast)->left->right->str, " no such job.");
		}
		return (1);
	}
	else
		ft_errormsg("42sh: bg: ", NULL, "no currrent job.");
	return (0);
}


int			foreground(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;

	(void)job;
	if (*table)
	{
		j = *table;
		if (j)
		{
			if ((j = find_pgid(table, ast)))
			{
				mark_job_as_running(&j);
				if (kill(-j->pgid, SIGCONT) < 0)
					perror("kill (SIGCONT)");
				tcsetpgrp(g_shell_terminal, j->pgid);
				wait_for_job(&j);
				tcsetpgrp(g_shell_terminal, g_shell_pgid);
			}
			else
				ft_errormsg("42sh: fg: ",
					(*ast)->left->right->str, " no such jobs");
		}
		return (1);
	}
	ft_putendl_fd("42sh: fg: current: no such job", 2);
	return (0);
}
