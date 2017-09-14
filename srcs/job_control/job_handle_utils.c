/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_handle_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:45:35 by nbouchin          #+#    #+#             */
/*   Updated: 2017/09/14 17:36:50 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_joblstadd(t_job **new, t_ast **ast, t_job **table)
{
	t_job	*tmp;
	t_job	*swap;
	int		i;

	i = 1;
	(void)ast;
	swap = *table;
	if (*table)
	{
		tmp = *table;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = *new;
	}
	else
	{
		*table = *new;
		(*table)->num = 1;
	}
	while (swap)
	{
		swap->num = i;
		i++;
		swap = swap->next;
	}
	return (1);
}

void	relink(t_process **tmp, t_process **del)
{
	ft_freetab((*tmp)->argv);
	(*tmp)->pid = 0;
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
