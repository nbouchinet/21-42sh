/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 16:39:01 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/25 12:17:38 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int            ctrlt(t_cmdl *cmdl)
{
    int        i;
    char    stock;
    int        min;

	if (cmdl->opt & (CCOMP | CCMODE))
		return (beep());
    i = cmdl->line.cur - cmdl->line.pr;
    if (i == 0 || ft_strlen(cmdl->line.str) < 2)
        return (beep());
    min = ((i == (int)ft_strlen(cmdl->line.str)) ? 1 : 0);
    stock = cmdl->line.str[i - min - 1];
    cmdl->line.str[i - min - 1] = cmdl->line.str[i - min];
    cmdl->line.str[i - min] = stock;
    arrow_left(cmdl);
    min == 1 ? arrow_left(cmdl) : 0;
    write(1, (cmdl->line.str + (i - min - 1)), 2 + min);
    cmdl->line.cur += 2;
    if (cmdl->line.cur % cmdl->line.co == 0)
        tputs(tgetstr("do", NULL), 1, ft_putchar);
    return (1);
}

int			ctrl_u(t_cmdl *cmdl)
{
	char	*sub;

	if (cmdl->opt & (CCOMP | CCMODE))
		return (beep());
	sub = ft_strdup(cmdl->line.str + (cmdl->line.cur - cmdl->line.pr));
	home(cmdl);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
	cmdl->line.str = ft_strcat(cmdl->line.str, sub);
	cmdl->line.cur = ft_strlen(cmdl->line.str) + cmdl->line.pr;
	write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
	home(cmdl);
	free(sub);
	return (1);
}

static void	register_cmdl(t_cmdl *cmdl)
{
	cmdl->line.str = ft_strjoinf(cmdl->line.save, cmdl->line.str, 0);
	cmd_save_history(cmdl->line.str);
}

int			ctrl_d(t_cmdl *cmdl)
{
	if (cmdl->line.str && !cmdl->line.str[0] &&
		((cmdl->opt & (CPIPE | CAND | COR))))
	{
		register_cmdl(cmdl);
		return (fd_printf(2, "\n42sh: syntax error: unexpected end of file"));
	}
	else if (cmdl->line.str && !cmdl->line.str[0] && (cmdl->opt & (CSQ | CDQ)))
	{
		register_cmdl(cmdl);
		return (fd_printf(2, "\n42sh: unexpected EOF while looking for a "
		"matching `%c'\n42sh: syntax error: unexpected end of file",
		cmdl->opt & CSQ ? '\'' : '"'));
	}
	else if (cmdl->line.str && cmdl->line.str[0])
		return (0);
	if (cmdl->line.save && !cmdl->line.str[0])
		ft_strdel(&cmdl->line.save);
	if (cmdl->line.str && !cmdl->line.str[0])
	{
		ft_strdel(&cmdl->line.str);
		cmdl->opt |= CCTRLD;
		return (1);
	}
	return (0);
}

int			ctrl_l(t_cmdl *cmdl)
{
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	print_prompt();
	if (cmdl->opt & CHIS_S && (cmdl->opt &= ~(CHIS_S)) && cmdl->line.str[0])
	{
		ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
		ft_strcpy(cmdl->line.str,
		findcmdl(cmdl->line.str, cmdl->line.buf, 2)->cmdl);
		write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
		cmdl->line.cur = ft_strlen(cmdl->line.str) + cmdl->line.pr;
	}
	else if (cmdl->opt & CCOMP)
	{
		write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
		display_comp(cmdl, &cmdl->comp, cmdl->offset);
	}
	else if (cmdl->line.str[0])
		write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
	return (1);
}
