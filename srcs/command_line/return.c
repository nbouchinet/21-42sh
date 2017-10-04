/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 17:35:33 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/25 12:18:39 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			exit_search_mode(t_cmdl *cmdl)
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
		return (RETURN(cmdl->line.buf) ? 1 : 2);
	}
	str = his->cmdl;
	ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
	cmdl->line.str = ft_strcpy(cmdl->line.str, str);
	write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
	cmdl->line.cur = ft_strlen(cmdl->line.str) + 3;
	cmdl->line.pr = 3;
	cmdl->opt &= ~(CHIS_S);
	return (RETURN(cmdl->line.buf) ? 1 : 2);
}

static void	save_cmdl(t_cmdl **cmdl)
{
	if ((*cmdl)->line.str && (*cmdl)->line.str[0])
		(*cmdl)->line.save = ft_strjoinf((*cmdl)->line.save,
		(*cmdl)->line.str, 1);
	ft_memset((*cmdl)->line.str, 0, ft_strlen((*cmdl)->line.str));
}

static int	check_save(t_cmdl *cmdl)
{
	if (!cmdl->opt)
		return (1);
	if ((!cmdl->line.save) || !(check_quote(cmdl)))
		return (1);
	save_cmdl(&cmdl);
	return (0);
}

static int	check_cmdl(t_cmdl *cmdl, int len)
{
	(void)len;
	if (!(cmdl->opt & (CHIS_S | CPIPE | CAND | COR)) && check_quote(cmdl))
		save_cmdl(&cmdl);
	else if (!(cmdl->opt & (CSQ | CDQ | CHIS_S)) && handle_pipe_and_or(cmdl, 0))
		save_cmdl(&cmdl);
	else if (cmdl->line.str && !(cmdl->opt & (CSQ | CDQ | CHIS_S | CPIPE | CAND
	| COR)) && cmdl->line.str[len > 0 ? len : 0] == '\\' &&
	inhibiteur(cmdl, len))
		save_cmdl(&cmdl);
	else if (check_save(cmdl))
		return (1);
	return (0);
}

int			return_cmdl(t_cmdl *cmdl)
{
	t_comp	*tmp;

	if (cmdl->opt & CCMODE)
		return (beep() == OK ? 1 : 1);
	if (cmdl->opt & CCOMP)
	{
		cmdl->opt &= ~(CCOMP);
		tmp = cmdl->comp;
		while (tmp && !tmp->bol)
			tmp = tmp->n;
		completion_edit(&cmdl->line, &tmp, NULL, cmdl->offset);
		cmdl->offset = -1;
		!(cmdl->line.cur % cmdl->line.co) ?
		tputs(tgetstr("do", NULL), 1, ft_putchar) : 0;
		comp_del(&cmdl->comp);
		return (1);
	}
	if ((!(cmdl->opt & CHIS_S) && check_cmdl(cmdl, ft_strlen(cmdl->line.str)
	- 1)) || ((cmdl->opt & CHIS_S) && exit_search_mode(cmdl) == 1))
		return (2);
	return (1);
}
