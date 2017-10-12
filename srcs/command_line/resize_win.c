/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 20:49:22 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/12 20:49:28 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void 	ccp_case(t_cmdl *cmdl, int save)
{
	cmdl->line.cur = write(1, cmdl->line.str, ft_strlen(cmdl->line.str))
	+ cmdl->line.pr;
	home(cmdl);
	end(cmdl);
	while (cmdl->line.cur > save)
		arrow_left(cmdl);
}

static void 	comp_case(t_cmdl *cmdl, int save)
{
	cmdl->line.cur = write(1, cmdl->line.str, ft_strlen(cmdl->line.str))
	+ cmdl->line.pr;
	while (cmdl->line.cur > save)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		cmdl->line.cur--;
	}
	if (cmdl->opt & CCOMP)
	{
		cmdl->opt &= ~CCMODE;
		display_comp(cmdl, &cmdl->comp, 0);
	}
}

static void 	search_hist_case(t_cmdl *cmdl, int save)
{
	t_his	*his;

	his = findcmdl(cmdl->line.str, 0, 2);
	cmdl->line.cur = 22 + ft_strlen(cmdl->line.str) +
	(his ? ft_strlen(his->cmdl) : 0);
	ft_printf("(reverse-i-search)`%s': %s", cmdl->line.str,
	his ? his->cmdl : "");
	while (cmdl->line.cur > save)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		cmdl->line.cur--;
	}
}

void 			resize_win(t_cmdl *cmdl, int save)
{
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	get_win_data(cmdl);
	print_prompt();
	if (cmdl->opt & CCP)
		ccp_case(cmdl, save);
	else if (cmdl->opt & CCOMP)
		comp_case(cmdl, save);
	else if (cmdl->opt & CHIS_S)
		search_hist_case(cmdl, save);
	else if (!cmdl->opt)
	{
		cmdl->line.cur = write(1, cmdl->line.str, ft_strlen(cmdl->line.str))
		+ cmdl->line.pr;
		while (cmdl->line.cur > save)
			arrow_left(cmdl);
	}
}
