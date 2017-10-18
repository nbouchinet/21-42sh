/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrlc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 20:52:55 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/15 13:01:01 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	search_hist_case(t_cmdl *cmdl)
{
	cmdl->opt = 0;
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	cmdl->line.cur = write(1, "$> ", 3);
	cmdl->line.cur = cmdl->line.pr;
	init_cmdl();
}

static void	ccp_case_c(t_cmdl *cmdl)
{
	cmdl->opt = 0;
	cmdl->ccp.start = -1;
	cmdl->ccp.end = -1;
	cmdl->ccp.ccp = -1;
	end(cmdl);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	write(1, "\n", 1);
	print_prompt();
	init_cmdl();
}

static void	comp_case(t_cmdl *cmdl)
{
	cmdl->opt = 0;
	end(cmdl);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	write(1, "\n", 1);
	print_prompt();
	init_cmdl();
}

void		handle_ctrlc(t_cmdl *cmdl)
{
	if (cmdl->opt & CCOMP)
		comp_case(cmdl);
	else if (cmdl->opt & CCP)
		ccp_case_c(cmdl);
	else if (cmdl->opt & CHIS_S)
		search_hist_case(cmdl);
	else if (!cmdl->opt || (cmdl->opt & (CAND | COR | CPIPE | CDQ | CSQ | CBS)))
	{
		cmdl->opt = 0;
		end(cmdl);
		write(1, "\n", 1);
		print_prompt();
		init_cmdl();
	}
}
