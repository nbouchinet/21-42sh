/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 16:39:01 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/11 20:55:35 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void register_cmdl(t_cmdl *cmdl)
{
	cmdl->line.str = ft_strjoinf(cmdl->line.save, cmdl->line.str, 0);
	cmd_save_history(cmdl->line.str);
}

int		ctrl_d(t_cmdl *cmdl)
{
	if (cmdl->line.str && !cmdl->line.str[0] &&
	    ((cmdl->opt & (CPIPE | CAND | COR))))
	{
		register_cmdl(cmdl);
		return (fd_printf(2, "\n42sh: syntax error: unexpected end of file"));
	}
	else if (cmdl->line.str && !cmdl->line.str[0] &&
	         (cmdl->opt & CSQ || cmdl->opt & CDQ))
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
	if (cmdl->opt & CHIS_S)
	{
		ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
		ft_strcpy(cmdl->line.str,
		findcmdl(cmdl->line.str, cmdl->line.buf, 2)->cmdl);
		write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
		cmdl->opt &= ~(CHIS_S);
		cmdl->line.cur = ft_strlen(cmdl->line.str) + cmdl->line.pr;
	}
	else if (cmdl->line.str[0])
		write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
	return (1);
}
