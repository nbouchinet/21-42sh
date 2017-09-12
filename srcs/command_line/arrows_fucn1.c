/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows_fucn1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 15:59:01 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/11 19:56:12 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		up_dwn(t_cmdl *cmdl)
{
	int		tmp;
	int		len;

	if (cmdl->opt & CHIS_S)
		return (return_cmdl(cmdl));
	tmp = cmdl->line.co + 1;
	len = ft_strlen(cmdl->line.str);
	if (OPT_D(cmdl->line.buf) && cmdl->line.cur + cmdl->line.co - cmdl->line.pr
	>= len && len >= cmdl->line.co)
		while (cmdl->line.str[cmdl->line.cur - cmdl->line.pr])
			arrow_rigth(cmdl);
	else if (OPT_U(cmdl->line.buf) && cmdl->line.cur >= cmdl->line.co)
		while (--tmp)
			arrow_left(cmdl);
	else if (OPT_D(cmdl->line.buf) && len >= cmdl->line.co - cmdl->line.pr)
		while (--tmp)
			arrow_rigth(cmdl);
	return (1);
}

int	 	home(t_cmdl *cmdl)
{
	if (cmdl->opt & CHIS_S)
		return (return_cmdl(cmdl));
	if (cmdl->line.str[0])
		while (cmdl->line.cur > cmdl->line.pr)
			arrow_left(cmdl);
	return (1);
}

int	 	end(t_cmdl *cmdl)
{
	if (cmdl->opt & CHIS_S)
		return (return_cmdl(cmdl));
	if (cmdl->line.str[0])
		while (cmdl->line.str[cmdl->line.cur - cmdl->line.pr])
			arrow_rigth(cmdl);
	return (1);
}


int		arrow_rigth(t_cmdl *cmdl)
{
	if (cmdl->opt & CHIS_S)
		return (return_cmdl(cmdl));
	if (!cmdl->line.str[cmdl->line.cur - cmdl->line.pr])
		return (beep());
	cmdl->line.cur += 1;
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
	if (cmdl->line.cur == cmdl->line.pr)
		return (beep());
	if (cmdl->line.cur % cmdl->line.co == 0)
	{
		while (++i < cmdl->line.co)
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	cmdl->line.cur -= 1;
	return (1);
}
