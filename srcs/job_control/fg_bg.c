/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 00:22:12 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/04 16:31:34 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	wait_for_job(t_job **job)
{
	pid_t		pid;
	t_process	*p;

	p = (*job)->first_process;
	pid = waitpid(p->pid, &p->status, WUNTRACED);
	catch_error(job, p->status);
	mark_job_status(job, p->status, pid);
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
				ft_errormsg("42sh: bg: ", (*ast)->left->right->str,
					" no such job.");
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
				wait_for_job(&j); // find alternative
				tcsetpgrp(g_shell_terminal, g_shell_pgid);
				return (return_exec(j->first_process->status));
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
