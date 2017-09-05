/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:33:47 by nbouchin          #+#    #+#             */
/*   Updated: 2017/09/05 13:32:12 by zadrien          ###   ########.fr       */
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
			while(p)
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
				delete_tnode(&j, &prev, table);
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
	int			i;
	t_job		*j;

	i = 1;
	(void)job;
	(void)ast;
	if (*table)
	{
		j = *table;
		while (j)
		{
			printf("[%d] %d\t\t\t%s\n", i, j->pgid, j->command);
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
	static const t_tab	state[6] = {{ADD, &ft_joblstadd},
									{CHK, &check_job}, {FG, &foreground},
									{SUS, &sus_pid}, {UPT, &update_status},
									{BUILTIN, &builtin_job}};

	i = -1;
	while (++i < 6)
		if (state[i].mod == mod)
			if (state[i].f(job, ast, &table) == 1)
				return (1);
	return (0);
}
