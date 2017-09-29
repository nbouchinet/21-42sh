/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 16:06:23 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/25 14:53:51 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_his		**his_slg(void)
{
	static t_his	*his = NULL;

	if (!his)
	{
		if (!(his = (t_his *)malloc(sizeof(t_his))))
			exit(0);
		his->cmdl = "";
		his->n = NULL;
		his->p = NULL;
	}
	return (&his);
}

void		init_cmdl(void)
{
	t_cmdl	*cmdl;

	cmdl = *cmdl_slg();
	cmdl->opt = 0;
	cmdl->col = 0;
	cmdl->offset = -1;
	cmdl->exit = 256;
	cmdl->comp = NULL;
	cmdl->line.str ? ft_strdel(&cmdl->line.str) : 0;
	cmdl->line.str = ft_memalloc(1024);
	cmdl->line.save ? ft_strdel(&cmdl->line.save) : 0;
	cmdl->ccp.cpy ? ft_strdel(&cmdl->ccp.cpy) : 0;
	cmdl->line.len = 1024;
	cmdl->line.cur = 3;
	cmdl->line.pr = 3;
	cmdl->ccp.start = -1;
	cmdl->ccp.end = -1;
	cmdl->ccp.ccp = 0;
}

t_cmdl		**cmdl_slg(void)
{
	static t_cmdl	*cmdl = NULL;

	if (!cmdl)
	{
		if (!(cmdl = (t_cmdl *)malloc(sizeof(t_cmdl))))
			exit(0);
		cmdl->line.str = NULL;
		cmdl->line.save = NULL;
		cmdl->ccp.cpy = NULL;
	}
	return (&cmdl);
}

t_local		**local_slg(int mode)
{
	static t_local *loc = NULL;

	if (!loc && mode)
	{
		if (!(loc = (t_local*)malloc(sizeof(t_local))))
			exit(fd_printf(2, "malloc error\n"));
		loc->var = NULL;
		loc->val = NULL;
		loc->n = NULL;
		loc->p = NULL;
	}
	return (&loc);
}
