/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 16:56:27 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/15 16:56:42 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void stock_loc(t_local *loc, char *str, char *sub, int match)
{
	if (match)
	{
		if (!(loc->n = (t_local*)malloc(sizeof(t_local))))
		  exit(fd_printf(2, "malloc error\n"));
		loc->n->var = ft_strdup(str);
		loc->n->val = ft_strdup(sub);
		loc->n->n = NULL;
		loc->n->p = loc;
	}
	else
	{
		loc->var = ft_strdups(str, &loc->var);
		loc->val = ft_strdups(sub, &loc->val);
	}
}

int   local(char *str)
{
	t_local		*loc;
	char		*sep;
	char		*sub;
	int			match;

	loc = *local_slg();
	if (!(sep = ft_strchr(str, '=')))
		return (1);
	sub = ft_strdup(str + 1);
	*str = 0;
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
	stock_loc(loc, str, sub, match);
	ft_strdel(&sub);
	return (1);
}
