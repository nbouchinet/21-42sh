/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ccp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 14:54:12 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/25 12:15:47 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	swap(t_cmdl *cmdl, int w, int i)
{
	int		tmp;

	if (!w)
	{
		tmp = cmdl->ccp.start + 1;
		cmdl->ccp.start = cmdl->ccp.end - (cmdl->ccp.end ? 1 : 0);
		cmdl->ccp.end = tmp;
	}
	else
	{
		while ((cmdl->line.cur - cmdl->line.pr) < cmdl->ccp.end)
		{
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
			cmdl->line.cur++;
			!(cmdl->line.cur % cmdl->line.co) ?
			tputs(tgetstr("do", NULL), 1, ft_putchar) : 0;
		}
		while (i--)
			del(cmdl);
	}
}

static void	get_b_e(t_cmdl *cmdl)
{
	if (cmdl->ccp.start != -1 && cmdl->ccp.end == -1)
		cmdl->ccp.end = cmdl->line.cur - cmdl->line.pr +
		(cmdl->line.cur - cmdl->line.pr ? 1 : 0);
	if (cmdl->ccp.start == -1 && cmdl->ccp.end == -1)
		cmdl->ccp.start = cmdl->line.cur - cmdl->line.pr;
	if (cmdl->ccp.end != -1)
		cmdl->opt &= ~CCP;
}

static void	mark_b_e(t_cmdl *cmdl)
{
	int		i;

	get_b_e(cmdl);
	if (cmdl->ccp.cpy)
		ft_strdel(&cmdl->ccp.cpy);
	if (cmdl->ccp.end == -1)
		return ;
	if (cmdl->ccp.start + 1 == cmdl->ccp.end &&
	cmdl->ccp.start == (int)ft_strlen(cmdl->line.str))
	{
		cmdl->ccp.end = -1;
		return ;
	}
	if (cmdl->ccp.start > cmdl->ccp.end)
		swap(cmdl, 0, 0);
	!(cmdl->ccp.end - cmdl->ccp.start) ? arrow_right(cmdl) : 0;
	i = (cmdl->ccp.end - cmdl->ccp.start) ? (cmdl->ccp.end - cmdl->ccp.start) :
	1;
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
	int		st;

	if (cmdl->opt & (CHIS_S | CCMODE | CCOMP))
		return (write(2, "\7", 1));
	cmdl->opt |= CCP;
	if (PST(cmdl->line.buf) && cmdl->ccp.cpy)
		return (paste(cmdl, ft_strlen(cmdl->ccp.cpy)));
	if (PST(cmdl->line.buf) && cmdl->ccp.end == -1)
		return (1);
	if ((CUT(cmdl->line.buf) && cmdl->ccp.ccp == 2)
	|| (CPY(cmdl->line.buf) && cmdl->ccp.ccp == 1) || cmdl->ccp.cpy)
	{
		cmdl->ccp.start = -1;
		cmdl->ccp.end = -1;
		st = cmdl->line.cur;
		home(cmdl);
		write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
		cmdl->line.cur = ft_strlen(cmdl->line.str) + cmdl->line.pr;
		while (cmdl->line.cur > st)
			arrow_left(cmdl);
	}
	cmdl->ccp.ccp = CUT(cmdl->line.buf) ? 1 : 2;
	mark_b_e(cmdl);
	(cmdl->ccp.start != -1 && cmdl->ccp.end != -1) ? unrev_color(cmdl) : 0;
	return (1);
}
