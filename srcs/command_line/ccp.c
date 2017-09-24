/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ccp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 14:54:12 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/11 19:57:36 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	swap(t_cmdl *cmdl, int w, int i)
{
	int		tmp;

	(void)i;
	if (!w)
	{
		tmp = cmdl->ccp.start;
		cmdl->ccp.start = cmdl->ccp.end;
		cmdl->ccp.end = tmp;
	}
	else
	{
		if (cmdl->line.cur == 3)
			return ;
		while (i--)
			del(cmdl);
	}
}

static void	get_b_e(t_cmdl *cmdl)
{
	if (CUT(cmdl->line.buf))
	{
		cmdl->ccp.start != -1 && cmdl->ccp.end == -1 ?
		cmdl->ccp.end = cmdl->line.cur - cmdl->line.pr : 0;
		cmdl->ccp.start == -1 && cmdl->ccp.end == -1 ?
		cmdl->ccp.start = cmdl->line.cur - cmdl->line.pr : 0;
	}
	else if (CPY(cmdl->line.buf))
	{
		cmdl->ccp.start != -1 && cmdl->ccp.end == -1 ?
		cmdl->ccp.end = cmdl->line.cur - cmdl->line.pr : 0;
		cmdl->ccp.start == -1 && cmdl->ccp.end == -1 ?
		cmdl->ccp.start = cmdl->line.cur - cmdl->line.pr : 0;
	}
}

static void	mark_b_e(t_cmdl *cmdl)
{
	int		i;

	get_b_e(cmdl);
	if (cmdl->ccp.end == -1)
		return ;
	if (cmdl->ccp.start > cmdl->ccp.end)
		swap(cmdl, 0, 0);
	i = cmdl->ccp.end - cmdl->ccp.start;
	if (cmdl->ccp.cpy)
		ft_strdel(&cmdl->ccp.cpy);
	cmdl->ccp.cpy = ft_strsub(cmdl->line.str, cmdl->ccp.start, i);
	if (CUT(cmdl->line.buf))
		swap(cmdl, 1, i);
}

static void	unrev_color(t_cmdl *cmdl)
{
	int		i;

	i = cmdl->line.cur;
	end(cmdl);
	home(cmdl);
	while (cmdl->line.cur < i)
		arrow_right(cmdl);
}

int			ccp(t_cmdl *cmdl)
{
	if (cmdl->opt & (CHIS_S | CCMODE | CCOMP))
		return (beep());
	if (PST(cmdl->line.buf) && cmdl->ccp.cpy)
	{
		return (paste(cmdl, ft_strlen(cmdl->ccp.cpy),
		ft_strlen(cmdl->line.str)));
	}
	if (PST(cmdl->line.buf) && cmdl->ccp.end == -1)
		return (1);
	if ((CUT(cmdl->line.buf) && cmdl->ccp.ccp == 2) ||
	(CPY(cmdl->line.buf) && cmdl->ccp.ccp == 1))
	{
		cmdl->ccp.start = -1;
		cmdl->ccp.end = -1;
	}
	cmdl->ccp.ccp = CUT(cmdl->line.buf) ? 1 : 2;
	mark_b_e(cmdl);
	if (cmdl->ccp.start != -1 && cmdl->ccp.end != -1)
		unrev_color(cmdl);
	return (1);
}
