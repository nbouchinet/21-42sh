/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_all.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 12:56:49 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/10 22:25:38 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	del_loc(t_local **loc_head)
{
	t_local		*loc;
	t_local		*save;

	loc = *loc_head;
	while (loc)
	{
		save = loc->n;
		ft_strdel(&loc->var);
		ft_strdel(&loc->val);
		free(loc);
		loc = save;
	}
	loc = NULL;
}

static void	del_his(t_his **his_head)
{
	t_his		*his;
	t_his		*save;

	his = *his_head;
	while (his)
	{
		save = his->n;
		if (his != *his_head)
			ft_strdel(&his->cmdl);
		free(his);
		his = save;
	}
	his = NULL;
}

void		del_all(t_cmdl **cmdl_head, t_his **his_head, t_local **loc_head)
{
	t_cmdl		*cmdl;

	cmdl = *cmdl_head;
	if (cmdl->line.str)
		ft_strdel(&cmdl->line.str);
	if (cmdl->line.save)
		ft_strdel(&cmdl->line.save);
	if (cmdl->ccp.cpy)
		ft_strdel(&cmdl->ccp.cpy);
	if (cmdl->pwd)
		ft_strdel(&cmdl->pwd);
	if (his_head)
		del_his(his_head);
	if (loc_head)
		del_loc(loc_head);
}
