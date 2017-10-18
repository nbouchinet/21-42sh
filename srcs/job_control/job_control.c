/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 00:09:20 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/18 14:32:33 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		job_control(t_job **job, t_ast **ast, int mod)
{
	int					i;
	static t_job		*table = NULL;
	static const t_tab	state[6] = {{ADD, &ft_joblstadd},
									{CHK, &check_job}, {FG, &foreground},
									{UPT, &update_status},
									{BUILTIN, &builtin_job}, {BG, &background}};

	i = -1;
	while (++i < 6)
		if (state[i].mod == mod)
			if (state[i].f(job, ast, &table) == 1)
				return (1);
	return (0);
}

int		ft_joblstadd(t_job **new, t_ast **ast, t_job **table)
{
	t_job	*tmp;
	int		prev;

	prev = 0;
	(void)ast;
	if (*table)
	{
		tmp = *table;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *new;
		(*new)->num = tmp->num + 1;
	}
	else
	{
		*table = *new;
		(*table)->num = 1;
	}
	return (1);
}

int		check_job(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;
	t_job		*prev;

	(void)job;
	(void)ast;
	prev = NULL;
	if ((j = *table))
		while (j)
		{
			if (check_kill(&j))
			{
				delete_tnode(&j, &prev, table);
				if ((j = *table))
					prev = NULL;
				else
					j = NULL;
			}
			else
			{
				prev = j;
				j = j->next;
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
	if ((j = *table))
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
	return (1);
}

int		builtin_job(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;
	int			len;
	int			status;
	int			pos;

	j = NULL;
	pos = 0;
	len = 0;
	status = 0;
	update_status(job, ast, table);
	if (*table)
	{
		job_len(&j, table, &len);
		print_job_message(&j, &len, &pos);
	}
	else
		ft_errormsg("42sh:", NULL, " No jobs.");
	return (1);
}
