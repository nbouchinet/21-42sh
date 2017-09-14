/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:33:47 by nbouchin          #+#    #+#             */
/*   Updated: 2017/09/14 17:24:40 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		end_pid(t_job **job, t_ast **ast, t_job **table)
{
	t_job	*head;
	t_job	*prev;

	(void)job;
	(void)ast;
	prev = NULL;
	head = (*table);
	while (*table)
	{
		prev = (*table);
		(*table) = (*table)->next;
	}
	delete_tnode(table, &prev, table);
	(*table) = head;
	return (1);
}

int		add_pid(t_job **job, t_ast **ast, t_job **table)
{
	(void)ast;
	ft_joblstadd(table, ast, job);
	return (1);
}

int		chk_pid(t_job **job, t_ast **ast, t_job **table)
{
	t_job	*tmp;
	t_job	*prev;

	(void)job;
	(void)ast;
	prev = NULL;
	if (*table)
	{
		tmp = *table;
		while (tmp)
		{
			if (job_is_complete(tmp))
			{
				delete_tnode(&tmp, &prev, table);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (1);
}

int		update_status(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;
	t_process	*p;

	(void)job;
	(void)ast;
	if (*table)
	{
		j = *table;
		while (j)
		{
			p = j->first_process;
			while (p)
			{
				waitpid(p->pid, &p->status, WUNTRACED | WCONTINUED | WNOHANG);
				p = p->next;
			}
			mark_process_status(&j);
			j = j->next;
		}
	}
	return (1);
}

int		check_job(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;
	t_job		*prev;

	(void)job;
	(void)ast;
	if (*table)
	{
		prev = NULL;
		j = *table;
		while (j)
		{
			if (job_is_complete(j) == 1)
			{
				delete_tnode(&j, &prev, table);
				break ;
			}
			prev = j;
			j = j->next;
		}
	}
	return (1);
}

int		inter_job(t_ast **ast, t_env **env)
{
	(void)ast;
	(void)env;
	return (job_control(NULL, ast, BUILTIN));
}

int		builtin_job(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;
	int			len;
	int			status;
	char		symb;

	(void)job;
	(void)ast;
	len = 0;
	status = 0;
	if (*table)
	{
		j = *table;
		while (j)
		{
			j = j->next;
			len++;
		}
		j = *table;
		while (j)
		{
			if (len == j->num)
				symb = '+';
			else if (len - 1 == j->num)
				symb = '-';
			else
				symb = ' ';
			if (WTERMSIG(status) == SIGSEGV)
				fd_printf(2, "[%d]%c Segmentation fault: 11 %s\n", j->num, symb, j->command);
			else if (WTERMSIG(status) == SIGABRT)
				fd_printf(2, "[%d]%c Abort trap: 6 \t\t%s\n", j->num, symb, j->command);
			else if (WTERMSIG(status) == SIGTSTP)
				fd_printf(2, "[%d]%c Bus error: 10 \t\t%s\n", j->num, symb, j->command);
			else if (WTERMSIG(status) == 15)
				fd_printf(2, "[%d]%c Terminated: \t\t15 %s\n", j->num, symb, j->command);
			else
				fd_printf(2, "[%d]%c Stopped\t\t\t%s\n", j->num, symb, j->command);
			j = j->next;
		}
	}
	else
		ft_errormsg("42sh:", NULL, " No jobs.");
	return (1);
}

int		job_control(t_job **job, t_ast **ast, int mod)
{
	int					i;
	static t_job		*table = NULL;
	static const t_tab	state[7] = {{ADD, &ft_joblstadd},
									{CHK, &check_job}, {FG, &foreground},
									{SUS, &sus_pid}, {UPT, &update_status},
									{BUILTIN, &builtin_job}, {BG, &background}};

	i = -1;
	while (++i < 7)
		if (state[i].mod == mod)
			if (state[i].f(job, ast, &table) == 1)
				return (1);
	return (0);
}
