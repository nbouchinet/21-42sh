/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 18:06:32 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/11 10:38:51 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	bs(char *str, int i)
{
	int		count;

	count = 0;
	if (i == 0)
		return (0);
	while (str[--i] == '\\')
		count++;
	if (!count || (count % 2))
		return (1);
	return (0);
}

static void	count_quote(t_cmdl *cmdl)
{
	int		i;

	i = -1;
	while (cmdl->line.str[++i])
	{
		if (cmdl->line.str[i] == '\'' && (!(cmdl->opt & (CSQ | CDQ))) &&
				bs(cmdl->line.str, i))
			cmdl->opt |= CSQ;
		else if (cmdl->line.str[i] == '"' && (!(cmdl->opt & (CSQ | CDQ))) &&
				bs(cmdl->line.str, i))
			cmdl->opt |= CDQ;
		else if (cmdl->line.str[i] == '\'' && (cmdl->opt & CSQ) &&
				!bs(cmdl->line.str, i))
			cmdl->opt &= ~(CSQ);
		else if (cmdl->line.str[i] == '"' && (cmdl->opt & CDQ) &&
				!bs(cmdl->line.str, i))
			cmdl->opt &= ~(CDQ);
	}
}

int			check_quote(t_cmdl *cmdl)
{
	count_quote(cmdl);
	if ((cmdl->opt & (CSQ | CDQ)))
	{
		regular_print(&cmdl->line, cmdl->line.buf, cmdl->line.cur - cmdl->line.pr, 0);
		if (!(cmdl->opt & (CPIPE | COR | CAND)))
			cmdl->line.pr = (cmdl->opt & CSQ ?
				write(1, "\nquote> ", 8) - 1 : write(1, "\ndquote> ", 9) - 1);
		else if (cmdl->opt & (CPIPE | COR | CAND))
		{
			cmdl->line.pr = ((cmdl->opt & COR) && (cmdl->opt & CSQ) ?
					write(1, "\ncmdor quote> ", 14) - 1 : cmdl->line.pr);
			cmdl->line.pr = ((cmdl->opt & COR) && (cmdl->opt & CDQ) ?
					write(1, "\ncmdor dquote> ", 15) - 1 : cmdl->line.pr);
			cmdl->line.pr = ((cmdl->opt & CAND) && (cmdl->opt & CSQ) ?
					write(1, "\ncmdand quote> ", 15) - 1 : cmdl->line.pr);
			cmdl->line.pr = ((cmdl->opt & CAND) && (cmdl->opt & CDQ) ?
					write(1, "\ncmdand dquote> ", 16) - 1 : cmdl->line.pr);
			cmdl->line.pr = ((cmdl->opt & CPIPE) && (cmdl->opt & CSQ) ?
					write(1, "\npipe quote> ", 13) - 1 : cmdl->line.pr);
			cmdl->line.pr = ((cmdl->opt & CPIPE) && (cmdl->opt & CDQ) ?
					write(1, "\npipe dquote> ", 14) - 1 : cmdl->line.pr);
		}
		return ((cmdl->line.cur = cmdl->line.pr) ? 1 : 1);
	}
	return (0);
}
