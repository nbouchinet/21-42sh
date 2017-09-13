/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 14:12:07 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/13 09:22:14 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		unset_env(t_env **env, char *str)
{
	t_env		*tmp;
	t_env		*prev;

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

static int		unset_lst(char *str)
{
	t_local		*loc;
	t_local		*prev;

	loc = *local_sgt(0);
	prev = NULL;
	if (!loc)
		return (0);
	while (loc && ft_strcmp(str, loc->var))
	{
		prev = loc;
		loc = loc->n;
	}
	if (!loc)
		return (0);
	free(loc->var);
	free(loc->val);
	if (prev)
		prev->n = loc->n;
	else if (!prev && loc->n)
		*local_sgt(0) = loc->n;
	else if (!prev && !loc->n)
		*local_sgt(0) = NULL;
	free(loc);
	return (1);
}

int				ft_unset(t_ast **ast, t_env **env)
{
	if (!(*ast)->left->right)
		return (0);
	if (unset_lst((*ast)->left->right->str))
	{
		unset_env(env, (*ast)->left->right->str);
		return (1);
	}
	return (0);
}
