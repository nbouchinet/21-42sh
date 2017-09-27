/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2017/09/19 15:32:04 by nbouchin         ###   ########.fr       */
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
				j->status = WTERMSIG(p->status);
				if (!j->next && j->notified != 1)
					catch_error(&j, p->status);
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
			if (kill(j->pgid, 0) < 0)
			{
				delete_tnode(&j, &prev, table);
				if (*table)
				{
					j = *table;
					prev = NULL;
				}
				else
					break ;
			}
			else
			{
				prev = j;
				j = j->next;
			}
		}
	}
	return (1);
}

int		inter_job(t_ast **ast, t_env **env)
{
	(void)env;
	(*ast)->right ? io_seq(&(*ast)->right->right) : 0;
	return (job_control(NULL, ast, BUILTIN));
}

int		builtin_job(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;
	int			len;
	int			status;
	char		symb;
	int			pos;

	(void)job;
	(void)ast;
	pos = 0;
	len = 0;
	status = 0;
	update_status(job, ast, table);
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
			pos++;
			if (len == pos)
				symb = '+';
			else if (len - 1 == pos)
				symb = '-';
			else
				symb = ' ';
			if (j->status == SIGSEGV)
				fd_printf(2, "[%d]%c Segmentation fault: 11 \t%s\n", j->num, symb, j->command);
			else if (j->status == SIGABRT)
				fd_printf(2, "[%d]%c Abort trap: 6 \t\t%s\n", j->num, symb, j->command);
			else if (j->status == SIGTSTP)
				fd_printf(2, "[%d]%c Bus error: 10 \t\t%s\n", j->num, symb, j->command);
			else if (j->status == 15)
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
