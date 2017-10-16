/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 14:44:23 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/10 22:24:22 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		delete_sh(t_cmdl *cmdl)
{
	t_his	*match;
	int		len;

	if ((cmdl->line.cur - cmdl->line.pr) == 0)
		return (1);
	match = findcmdl(cmdl->line.str, cmdl->line.buf, 2);
	len = ft_strlen(match->cmdl) + 4;
	cmdl->line.cur -= 1;
	if (cmdl->line.cur == 19)
		findcmdl(cmdl->line.str, 0, 1);
	cmdl->line.str[cmdl->line.cur - cmdl->line.pr] = 0;
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	tputs(tgetstr("le", NULL), 1, ft_putchar);
	tputs(tgetstr("dc", NULL), 1, ft_putchar);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	(cmdl->line.cur - cmdl->line.pr) == 0 ?
		write(1, "':", 2) : ft_printf("': %@", match->cmdl);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	return (1);
}

static int		delete_comp_lst(t_cmdl *cmdl)
{
	int		save_cmdl;

	save_cmdl = cmdl->line.cur - cmdl->line.pr;
	comp_del(&cmdl->comp);
	cmdl->opt &= ~CCOMP;
	end(cmdl);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	while (cmdl->line.cur - cmdl->line.pr > save_cmdl)
		arrow_left(cmdl);
	return (1);
}

int				back_del(t_cmdl *cmdl)
{
	int		i;

	i = cmdl->line.cur - cmdl->line.pr;
	if (cmdl->opt & CCOMP)
		return (delete_comp_lst(cmdl));
	if (cmdl->opt & (CCMODE | CHIS_S | CCP) ||
	i == (int)ft_strlen(cmdl->line.str))
		return (write(2, "\7", 1));
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	while (cmdl->line.str[i])
	{
		cmdl->line.str[i] = cmdl->line.str[i + 1];
		i++;
	}
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	write(1, cmdl->line.str + (cmdl->line.cur - cmdl->line.pr),
			ft_strlen(cmdl->line.str + (cmdl->line.cur - cmdl->line.pr)));
	tputs(tgetstr("me", NULL), 1, ft_putchar);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	return (1);
}

int				del(t_cmdl *cmdl)
{
	int		i;

	if (cmdl->opt & CHIS_S)
		return (delete_sh(cmdl));
	if (cmdl->opt & CCOMP)
		return (delete_comp_lst(cmdl));
	if (cmdl->opt & (CCMODE | CCP) || cmdl->line.cur == cmdl->line.pr)
		return (write(2, "\7", 1));
	arrow_left(cmdl);
	i = cmdl->line.cur - cmdl->line.pr - 1;
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	while (cmdl->line.str[++i])
		cmdl->line.str[i] = cmdl->line.str[i + 1];
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	write(1, cmdl->line.str + (cmdl->line.cur - cmdl->line.pr),
			ft_strlen(cmdl->line.str + (cmdl->line.cur - cmdl->line.pr)));
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	return (1);
}
