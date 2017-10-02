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

int		esc(t_cmdl *cmdl)
{
	int		save_cmdl;

	if (cmdl->opt & (CCOMP))
	{
		if (cmdl->comp)
			comp_del(&cmdl->comp);
		cmdl->comp = NULL;
		cmdl->opt &= ~CCOMP;
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
	}
	else if (cmdl->ccp.ccp)
	{
		cmdl->ccp.ccp = 0;
		cmdl->ccp.start = -1;
		cmdl->ccp.end = -1;
		save_cmdl = cmdl->line.cur - cmdl->line.pr;
		home(cmdl);
		write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
		cmdl->line.cur = ft_strlen(cmdl->line.str) + cmdl->line.pr;
		while (cmdl->line.cur - cmdl->line.pr > save_cmdl)
			arrow_left(cmdl);
	}
	return (1);
}
