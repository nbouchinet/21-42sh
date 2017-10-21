/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 16:39:01 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 22:26:07 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			ctrlt(t_cmdl *cmdl)
{
	int		i;
	char	stock;
	int		min;

	i = cmdl->line.cur - cmdl->line.pr;
	if (cmdl->opt & (CCOMP | CCMODE | CHIS_S) || !i ||
			ft_strlen(cmdl->line.str) < 2)
		return (write(2, "\7", 1));
	min = ((i == (int)ft_strlen(cmdl->line.str)) ? 1 : 0);
	stock = cmdl->line.str[i - min - 1];
	cmdl->line.str[i - min - 1] = cmdl->line.str[i - min];
	cmdl->line.str[i - min] = stock;
	arrow_left(cmdl);
	min == 1 ? arrow_left(cmdl) : 0;
	if (cmdl->ccp.start != -1 && cmdl->ccp.end == -1
			&& cmdl->line.cur - cmdl->line.pr >= cmdl->ccp.start)
		tputs(tgetstr("mr", NULL), 1, ft_putchar);
	cmdl->line.cur += write(1, (cmdl->line.str + (i - min - 1)), 1);
	if (cmdl->ccp.start != -1 && cmdl->ccp.end == -1
			&& cmdl->line.cur - cmdl->line.pr >= cmdl->ccp.start)
		tputs(tgetstr("mr", NULL), 1, ft_putchar);
	cmdl->line.cur += write(1, (cmdl->line.str + (i - min)), 1 + min) - min;
	if (cmdl->line.cur % cmdl->line.co == 0)
		tputs(tgetstr("do", NULL), 1, ft_putchar);
	return ((tputs(tgetstr("me", NULL), 1, ft_putchar) ? 1 : 1));
}

int			ctrl_u(t_cmdl *cmdl)
{
	char	*sub;

	if (cmdl->opt & (CCOMP | CCMODE | CCP | CHIS_S))
		return (write(2, "\7", 1));
	sub = ft_strdup(cmdl->line.str + (cmdl->line.cur - cmdl->line.pr));
	home(cmdl);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
	cmdl->line.str = ft_strcat(cmdl->line.str, sub);
	cmdl->line.cur = ft_strlen(cmdl->line.str) + cmdl->line.pr;
	write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
	home(cmdl);
	ft_strdel(&sub);
	return (1);
}

static int	register_cmdl(t_cmdl *cmdl, int w)
{
	char	*tmp;

	tmp = cmdl->line.str;
	if (!w)
		fd_printf(2, "\n42sh: syntax error: unexpected end of file\n");
	else
		fd_printf(2, "\n42sh: unexpected EOF while looking for a "
				"matching `%c'\n42sh: syntax error: unexpected end of file\n",
				cmdl->opt & CSQ ? '\'' : '"');
	cmdl->line.str = ft_strjoin(cmdl->line.save, cmdl->line.str);
	ft_strdel(&tmp);
	cmd_save_history(cmdl->line.str, 0);
	init_cmdl();
	return (1);
}

static int	cbs_case(t_cmdl *cmdl)
{
	char	*tmp;

	if (cmdl->line.str[0])
		return (0);
	tmp = cmdl->line.str;
	cmdl->line.str = ft_strjoin(cmdl->line.save, cmdl->line.str);
	*(ft_strrchr(cmdl->line.str, '\\')) = 0;
	ft_strdel(&tmp);
	ft_strdel(&cmdl->line.save);
	cmdl->opt &= ~CBS;
	return (1);
}

int			ctrl_d(t_cmdl *cmdl)
{
	if (cmdl->line.str && !cmdl->line.str[0] &&
		((cmdl->opt & (CPIPE | CAND | COR))))
		return (register_cmdl(cmdl, 0));
	else if (cmdl->line.str && !cmdl->line.str[0] && (cmdl->opt & (CSQ | CDQ)))
		return (register_cmdl(cmdl, 1));
	else if (cmdl->opt & CHD)
		return (cmdl->line.str && cmdl->line.str[0] ? 0 : 1);
	else if (cmdl->opt & CBS)
		return (cbs_case(cmdl));
	else if (cmdl->opt & CCOMP || (cmdl->line.str && cmdl->line.str[0]))
		return (write(1, "\7", 1) - 1);
	if (cmdl->line.save && !cmdl->line.str[0])
		ft_strdel(&cmdl->line.save);
	if (cmdl->line.str && !cmdl->line.str[0])
	{
		ft_strdel(&cmdl->line.str);
		cmdl->opt |= CCTRLD;
		return (set_exiting_value(&cmdl, 1));
	}
	return (0);
}
