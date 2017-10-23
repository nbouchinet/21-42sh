/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows_fucn1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 15:59:01 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 15:25:05 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		up_dwn(t_cmdl *cmdl)
{
	int		tmp;
	int		len;

	if (cmdl->opt & (CCMODE | CCOMP | CHIS_S))
		return (write(2, "\7", 1));
	tmp = cmdl->line.co + 1;
	len = ft_strlen(cmdl->line.str);
	if (OPT_D(cmdl->line.buf) && cmdl->line.cur + cmdl->line.co - cmdl->line.pr
	>= len && len >= cmdl->line.co)
		while (cmdl->line.str[cmdl->line.cur - cmdl->line.pr])
			arrow_right(cmdl);
	else if (OPT_U(cmdl->line.buf) && cmdl->line.cur >= cmdl->line.co)
		while (--tmp)
			arrow_left(cmdl);
	else if (OPT_D(cmdl->line.buf) && len >= cmdl->line.co - cmdl->line.pr)
		while (--tmp)
			arrow_right(cmdl);
	return (1);
}

int		home(t_cmdl *cmdl)
{
	if (cmdl->opt & (CCMODE | CCOMP))
		return (write(2, "\7", 1));
	if (cmdl->opt & CHIS_S)
		return (return_cmdl(cmdl));
	if (cmdl->line.str[0])
		while (cmdl->line.cur > cmdl->line.pr)
			arrow_left(cmdl);
	return (1);
}

int		end(t_cmdl *cmdl)
{
	if (cmdl->opt & (CCMODE | CCOMP))
		return (write(2, "\7", 1));
	if (cmdl->opt & CHIS_S)
		return (return_cmdl(cmdl));
	if (cmdl->line.str[0])
		while (cmdl->line.str[cmdl->line.cur - cmdl->line.pr])
			arrow_right(cmdl);
	return (1);
}

int		arrow_right(t_cmdl *cmdl)
{
	if (cmdl->opt & CHIS_S)
		return (return_cmdl(cmdl));
	if ((!(cmdl->opt & CCOMP) &&
	!cmdl->line.str[cmdl->line.cur - cmdl->line.pr]) || cmdl->opt & CCMODE)
		return (write(2, "\7", 1));
	if (cmdl->opt & CCOMP)
		return (c_arrow_right(&cmdl->comp));
	if (cmdl->ccp.start != -1 && cmdl->ccp.end == -1 &&
	cmdl->line.cur - cmdl->line.pr >= cmdl->ccp.start)
		tputs(tgetstr("mr", NULL), 1, ft_putchar);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	write(1, cmdl->line.str + (cmdl->line.cur - cmdl->line.pr), 1);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	tputs(tgetstr("me", NULL), 1, ft_putchar);
	cmdl->line.cur++;
	if (cmdl->line.cur % cmdl->line.co == 0)
		tputs(tgetstr("do", NULL), 1, ft_putchar);
	else
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
	return (1);
}

int		arrow_left(t_cmdl *cmdl)
{
	int		i;

	i = -1;
	if (cmdl->opt & CHIS_S)
		return (return_cmdl(cmdl));
	if ((!(cmdl->opt & CCOMP) && cmdl->line.cur == cmdl->line.pr) ||
	cmdl->opt & CCMODE)
		return (write(2, "\7", 1));
	if (cmdl->opt & CCOMP)
		return (c_arrow_left(&cmdl->comp));
	if (cmdl->ccp.start != -1 && cmdl->ccp.end == -1 &&
	cmdl->line.cur - cmdl->line.pr <= cmdl->ccp.start)
		tputs(tgetstr("mr", NULL), 1, ft_putchar);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	write(1, cmdl->line.str + (cmdl->line.cur - cmdl->line.pr), 1);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	tputs(tgetstr("me", NULL), 1, ft_putchar);
	if (cmdl->line.cur % cmdl->line.co == 0)
		while (++i < cmdl->line.co)
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	(cmdl->line.cur-- % cmdl->line.co == 0) ?
	tputs(tgetstr("up", NULL), 1, ft_putchar) : 0;
	return (1);
}
