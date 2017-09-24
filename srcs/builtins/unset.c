/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 14:12:07 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/17 14:12:14 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int unset_env(t_env **env, char *str)
{
	t_env     *tmp;
	t_env     *prev;

	tmp = *env;
	prev = NULL;
	while (tmp && ft_strcmp(tmp->var, str))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (0);
	free(tmp->var);
	free(tmp->value);
	if (prev)
		prev->next = tmp->next;
	else if (!prev && tmp->next)
		*env = tmp->next;
	else if (!prev && !tmp->next)
		*env = NULL;
	free(tmp);
	return (1);
}

static int unset_lst(char *str)
{
	t_local   *loc;

	loc = *local_slg();
	if (!loc)
		return (0);
	while (loc && ft_strcmp(str, loc->var))
		loc = loc->n;
	if (!loc)
		return (0);
	free(loc->var);
	free(loc->val);
	if (loc->p)
		loc->p->n = loc->n;
	else if (!loc->p && loc->n)
		*local_slg() = loc->n;
	else if (!loc->p && !loc->n)
		*local_slg() = NULL;
	free(loc);
	return (1);
}

int   ft_unset(t_ast **ast, t_env **env)
{
	t_ast	*tmp;

	if (!(*ast)->left->right)
		return (0);
	tmp = (*ast)->left->right;
	while (tmp->right)
	{
		if (unset_lst(tmp->str))
			unset_env(env, tmp->str);
		tmp = tmp->right;
	}
	return (1);
}
