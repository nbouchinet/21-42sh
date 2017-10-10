/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 16:56:27 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/10 20:50:38 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	stock_loc(t_local **loc, char *str, char *sub, int match)
{
	if (match)
	{
		if (!((*loc)->n = (t_local*)malloc(sizeof(t_local))))
			exit(fd_printf(2, "malloc error\n"));
		(*loc)->n->var = ft_strdup(str);
		(*loc)->n->val = ft_strdup(sub);
		(*loc)->n->n = NULL;
		(*loc)->n->p = (*loc);
	}
	else
	{
		ft_strdel(&(*loc)->val);
		(*loc)->val = ft_strdup(sub);
	}
}

int			put_into_lst(char *str, char *sub)
{
	t_local		*loc;
	int			match;

	loc = *local_slg(1);
	match = 0;
	if (!loc->var)
	{
		loc->var = ft_strdup(str);
		loc->val = ft_strdup(sub);
		ft_strdel(&sub);
		return (1);
	}
	while (loc->n && (match = ft_strcmp(loc->var, str)))
		loc = loc->n;
	if (!loc->n)
		(match = ft_strcmp(loc->var, str));
	stock_loc(&loc, str, sub, match);
	ft_strdel(&sub);
	return (1);
}

int			local(char *str)
{
	t_env	**env;
	t_env	*match;
	char	*sep;
	char	*sub;

	env = &(*cmdl_slg())->lstenv;
	sep = ft_strchr(str, '=');
	sub = ft_strdup(sep + 1);
	*sep = 0;
	if ((match = lst_at(env, str)))
	{
		ft_strdel(&match->value);
		match->value = ft_strdup(sub);
	}
	else
		put_into_lst(str, sub);
	return (1);
}
