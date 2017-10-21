/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 14:12:07 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/21 19:16:10 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		unset_env(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	if (!ft_strcmp(str, "PATH"))
		hash(NULL, NULL, CLEAN);
	while (tmp && ft_strcmp(tmp->var, str))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (0);
	ft_strdel(&tmp->var);
	ft_strdel(&tmp->value);
	if (prev)
		prev->next = tmp->next;
	else if (!prev && tmp->next)
		*env = tmp->next;
	else if (!prev && !tmp->next)
		*env = NULL;
	free(tmp);
	return (1);
}

static int		unset_lst(char *str)
{
	t_local		*loc;

	loc = *local_slg(0);
	if (!loc)
		return (0);
	while (loc && ft_strcmp(str, loc->var))
		loc = loc->n;
	if (!loc)
		return (0);
	ft_strdel(&loc->var);
	ft_strdel(&loc->val);
	if (loc->p)
		loc->p->n = loc->n;
	else if (!loc->p && loc->n)
		*local_slg(0) = loc->n;
	else if (!loc->p && !loc->n)
		*local_slg(0) = NULL;
	free(loc);
	return (1);
}

int				ft_unset(t_ast **ast, t_env **env)
{
	t_ast	*tmp;

	(*ast)->right ? io_seq(&(*ast)->right->right, 1) : 0;
	if (!(*ast)->left->right)
		return (0);
	tmp = (*ast)->left->right;
	while (tmp)
	{
		unset_lst(tmp->str);
		unset_env(env, tmp->str);
		tmp = tmp->right;
	}
	if (!*env)
		(*cmdl_slg())->lstenv = NULL;
	return (1);
}
