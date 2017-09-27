/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 15:24:18 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/25 15:07:00 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void add_to_env(t_env **env, t_local *loc)
{
	if (*env)
	{
		if (!((*env)->next = (t_env *)malloc(sizeof(t_env))))
		exit(fd_printf(2, "malloc error\n"));
		(*env)->next->var = ft_strdup(loc->var);
		(*env)->next->value = ft_strdup(loc->val);
		(*env)->next->next = NULL;
	}
	else
	{
		if (!((*env) = (t_env *)malloc(sizeof(t_env))))
		exit(fd_printf(2, "malloc error\n"));
		(*env)->var = ft_strdup(loc->var);
		(*env)->value = ft_strdup(loc->val);
		(*env)->next = NULL;
	}
}

static void check_local_lst(t_local **head, char *str)
{
	t_local	*tmp;
	char	*copy;
	char	*ptr;
	char	*sub;

	tmp = *head;
	copy = ft_strdup(str);
	ptr = ft_strchr(copy, '=');
	sub = ft_strdup(ptr + 1);
	*ptr = 0;
	while (tmp && ft_strcmp(tmp->var, copy))
		tmp = tmp->n;
	if (!tmp)
		local(str);
	free(copy);
	free(sub);
}

int			ft_export(t_ast **ast, t_env **env)
{
	t_local   *loc;
	t_env     *tmp;

	tmp = *env;
	if (!(*ast)->left->right)
		return (0);
	if (ft_strchr((*ast)->left->right->str, '='))
		check_local_lst(local_slg(0), (*ast)->left->right->str);
	loc = *local_slg(0);
	while (loc && ft_strcmp(loc->var, (*ast)->left->right->str))
		loc = loc->n;
	if (!loc)
		return (0);
	while (tmp && tmp->next)
		tmp = tmp->next;
	add_to_env(tmp ? &tmp : env, loc);
	return (1);
}
