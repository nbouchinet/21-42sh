/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 17:35:33 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/11 20:08:54 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int 		exit_search_mode(t_cmdl *cmdl)
{
	char	*str;

	str = findcmdl(cmdl->line.str, cmdl->line.buf, 0)->cmdl;
	while (cmdl->line.cur)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		cmdl->line.cur--;
	}
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
	cmdl->line.str = ft_strcpy(cmdl->line.str, str);
	write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
	cmdl->line.cur = ft_strlen(cmdl->line.str) + 3;
	cmdl->line.pr = 3;
	cmdl->opt &= ~(CHIS_S);
	return (RETURN(cmdl->line.buf) ? 1 : 2);
}

static void save_cmdl(t_cmdl **cmdl)
{
	if ((*cmdl)->line.str && (*cmdl)->line.str[0])
		(*cmdl)->line.save = ft_strjoinf((*cmdl)->line.save,
		(*cmdl)->line.str, 1);
	ft_memset((*cmdl)->line.str, 0, ft_strlen((*cmdl)->line.str));
}

static int	check_cmdl(t_cmdl *cmdl, int len)
{
	if (!(cmdl->opt & CHIS_S) && !(cmdl->opt & (CPIPE | CAND | COR)) && check_quote(cmdl)) // && !cmdl->hd
		save_cmdl(&cmdl);
	else if (!(cmdl->opt & (CSQ | CDQ)) && !(cmdl->opt & CHIS_S) &&
	         handle_pipe_and_or(cmdl, 0)) // && !cmdl->hd
		save_cmdl(&cmdl);
//	else if (!cmdl->sh && !cmdl->pao && !cmdl->quote && heredoc(cmdl))
// 		save_cmdl(&cmdl);
	else if (cmdl->line.str && !(cmdl->opt & CSQ)  && !(cmdl->opt & CDQ)
	         && !(cmdl->opt & CHIS_S) && !(cmdl->opt & (CPIPE | CAND | COR)) && cmdl->line.str[len] == '\\'
	         && inhibiteur(cmdl, len))
		save_cmdl(&cmdl);
	else
		return (1);
	return (0);
}

int 		return_cmdl(t_cmdl *cmdl)
{
	if (!(cmdl->opt & CHIS_S))
	{
		if (check_cmdl(cmdl, ft_strlen(cmdl->line.str) - 1))
		{
			!cmdl->line.str[0] ? write(1, "\n", 1) : 0;
			return (2);
		}
	}
	else
	{
		if (exit_search_mode(cmdl) == 1)
			return (2);
	}
	return (1);
}
