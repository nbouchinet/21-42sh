/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 15:24:18 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/21 19:16:04 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	handle_env(t_env **env, t_env **tmp)
{
	if (*env)
	{
		(*tmp) = *env;
		while ((*tmp)->next)
			(*tmp) = (*tmp)->next;
		if (!((*tmp)->next = (t_env *)malloc(sizeof(t_env))))
			exit(EXIT_FAILURE);
		(*tmp) = (*tmp)->next;
	}
	else
	{
		if (!((*tmp) = (t_env *)malloc(sizeof(t_env))))
			exit(EXIT_FAILURE);
		*env = *tmp;
		(*cmdl_slg())->lstenv = *env;
	}
}

static void	export_local(t_env **env, char *str)
{
	t_local		*local;
	t_env		*tmp;

	local = *local_slg(0);
	if (!local)
		return ;
	while (local && ft_strcmp(local->var, str))
		local = local->n;
	if (!local)
		return ;
	handle_env(env, &tmp);
	tmp->var = ft_strdup(local->var);
	tmp->value = ft_strdup(local->val);
	tmp->next = NULL;
}

static void	export_to_env(t_env **env, char *copy)
{
	t_env		*tmp;
	char		*ptr;
	char		*sub;

	if (!(ptr = ft_strchr(copy, '=')))
		return ;
	sub = ft_strdup(ptr + 1);
	*ptr = 0;
	tmp = lst_at(env, copy);
	if (!tmp)
	{
		handle_env(env, &tmp);
		tmp->var = ft_strdup(copy);
		tmp->value = ft_strdup(sub);
		tmp->next = NULL;
	}
	else
		tmp->value = ft_strdups(sub, &tmp->value);
	ft_strdel(&sub);
	ft_strdel(&copy);
}

int			ft_export(t_ast **ast, t_env **env)
{
	t_ast		*tmp;

	if ((*ast)->right)
		io_seq(&(*ast)->right->right, 1);
	tmp = (*ast)->left->right;
	while (tmp)
	{
		if (!ft_isalpha(tmp->str[0]))
		{
			return (fd_printf(2, "42sh: %s: not a valid identifier\n",
			tmp->str));
		}
		if (ft_strchr(tmp->str, '='))
		{
			export_to_env(env, ft_strdup(tmp->str));
			local(tmp->str);
		}
		else
			export_local(env, tmp->str);
		tmp = tmp->right;
	}
	return (1);
}
