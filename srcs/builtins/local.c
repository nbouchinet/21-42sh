/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 16:56:27 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/25 15:07:15 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void 	mod_env(t_env **env, char *str, char *sub)
{
	t_env 		*tmp;

	tmp = *env;
	if (!tmp)
		return ;
	while (tmp && ft_strcmp(tmp->var, str))
		tmp = tmp->next;
	if (!tmp)
		return ;
	tmp->value = ft_strdups(sub, &tmp->value);
}

static void 	stock_loc(t_local **loc, char *str, char *sub, int match)
{
	if (match)
	{
		ft_putendl(str);
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

int				local(char *str)
{
	t_local		*loc;
	char		*sep;
	char		*sub;
	int			match;

	loc = *local_slg(1);
	sep = ft_strchr(str, '=');
	sub = ft_strdup(sep + 1);
	*sep = 0;
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
	stock_loc(&loc, str, sub, match);
	mod_env(&(*cmdl_slg())->lstenv, str, sub);
	ft_strdel(&sub);
	return (1);
}
