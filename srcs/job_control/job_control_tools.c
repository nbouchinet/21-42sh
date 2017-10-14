/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 00:12:55 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/14 23:52:48 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		inter_job(t_ast **ast, t_env **env)
{
	(void)env;
	(*ast)->right ? io_seq(&(*ast)->right->right, 1) : 0;
	return (job_control(NULL, ast, BUILTIN));
}

void	relink(t_process **tmp, t_process **del)
{
	if ((*tmp)->argv)
		ft_freetab((*tmp)->argv);
	(*tmp)->pid = 0;
	(*tmp)->builtin = NULL;
	(*tmp)->rdir = NULL;
	*del = *tmp;
	(*tmp) = (*tmp)->next;
	(*del) ? free(*del) : 0;
}

void	delete_tnode(t_job **node, t_job **prev, t_job **table)
{
	t_process		*tmp;
	t_process		*del;

	if ((*node)->next)
		(*prev) ? ((*prev)->next =
		(*node)->next) : ((*table) = (*node)->next);
	else
		(*prev) ? ((*prev)->next = NULL)
		: ((*table) = NULL);
	if (*node)
	{
		ft_strdel(&(*node)->command);
		tmp = (*node)->first_process;
		while (tmp)
			relink(&tmp, &del);
		(*node)->first_process = NULL;
		(*node)->pgid = 0;
		free(*node);
	}
}

int		delete_process(t_process **head, t_process **prev, t_process **process)
{
	t_process	*p;

	p = *process;
	if (*prev)
		(*prev)->next = p->next;
	else
		*head = p->next;
	if (p->argv)
		ft_freetab(p->argv);
	p->builtin ? p->builtin = NULL : 0;
	p->rdir ? p->rdir = NULL : 0;
	p->env ? p->env = NULL : 0;
	p->completed = 0;
	p->stopped = 0;
	p->status = 0;
	p->next = NULL;
	free(p);
	return (1);
}

int		check_kill(t_job **job)
{
	t_process	*p;
	t_process	*prev;

	prev = NULL;
	p = (*job)->first_process;
	while (p)
	{
		if (kill(p->pid, 0) < 0)
		{
			// sleep(30);
			// ft_putendl("DELETE");
			delete_process(&(*job)->first_process, &prev, &p);
			p = (*job)->first_process;
		}
		else
			p = p->next;
	}
	if ((*job)->first_process == NULL)
		return (1);
	return (0);
}
