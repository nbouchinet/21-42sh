/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 20:51:13 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/18 16:02:58 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	freenode(t_env *node)
{
	ft_strdel(&node->var);
	if (node->value)
		ft_strdel(&node->value);
	free(node);
}

void	deletevar(t_env **tmp, t_env *prev)
{
	prev->next = (*tmp)->next;
	freenode(*tmp);
}

void	deletefirstnode(t_env **lst)
{
	t_env	*tmp;

	tmp = *lst;
	if (tmp->next)
		*lst = tmp->next;
	else
		*lst = NULL;
	freenode(tmp);
}

void	deletevarenv(t_env **lst, char *var)
{
	t_env	*prev;
	t_env	*tmp;

	prev = NULL;
	tmp = (*lst);
	if (!ft_strcmp(var, "PATH"))
		hash(NULL, NULL, CLEAN);
	while (tmp && ft_strcmp(tmp->var, var) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		ft_errormsg("42sh: ", var, ": Variable not set.");
	else if (!prev)
		deletefirstnode(lst);
	else if (tmp && ft_strcmp(tmp->var, var) == 0)
		deletevar(&tmp, prev);
}
