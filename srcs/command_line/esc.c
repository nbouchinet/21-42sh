/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 10:56:20 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/19 10:58:01 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void comp_case(t_cmdl *cmdl, int save)
{
	comp_del(&cmdl->comp);
	cmdl->opt &= ~CCOMP;
	end(cmdl);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	while (cmdl->line.cur - cmdl->line.pr > save)
		arrow_left(cmdl);
}

static void ccp_case(t_cmdl *cmdl, int save)
{
	cmdl->ccp.ccp = 0;
	cmdl->ccp.start = -1;
	cmdl->ccp.end = -1;
	home(cmdl);
	write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
	cmdl->line.cur = ft_strlen(cmdl->line.str) + cmdl->line.pr;
	while (cmdl->line.cur - cmdl->line.pr > save)
		arrow_left(cmdl);
	cmdl->opt &= ~CCP;
}

static void shis_case(t_cmdl *cmdl)
{
	t_his	*his;
	char	*str;

	his = findcmdl(cmdl->line.str, cmdl->line.buf, 2);
	str = NULL;
	while (cmdl->line.cur--)
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	if (!his)
	{
		init_cmdl();
		return ;
	}
	str = his->cmdl;
	ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
	cmdl->line.str = ft_strcpy(cmdl->line.str, str);
	write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
	cmdl->line.cur = ft_strlen(cmdl->line.str) + 3;
	cmdl->line.pr = 3;
	cmdl->opt &= ~(CHIS_S);
}

int			esc(t_cmdl *cmdl)
{
	int		save;

	save = cmdl->line.cur - cmdl->line.pr;
	if (cmdl->opt & CCOMP)
		comp_case(cmdl, save);
	else if (cmdl->opt & CHIS_S)
		shis_case(cmdl);
	else if (cmdl->ccp.ccp)
		ccp_case(cmdl, save);
	return (1);
}
