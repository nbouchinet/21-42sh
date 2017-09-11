/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 18:06:32 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/02 18:06:40 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void count_quote(t_cmdl *cmdl)
{
	int		i;

	i = -1;
	while (cmdl->line.str[++i])
	{
		if (cmdl->line.str[i] == '\'' && (!(cmdl->opt & (SQ | DQ))))
			cmdl->opt |= SQ;
		else if (cmdl->line.str[i] == '"' && (!(cmdl->opt & (SQ | DQ))))
			cmdl->opt |= (i == 0 || cmdl->line.str[i - 1] != '\\' ? DQ :
			cmdl->opt);
		else if (cmdl->line.str[i] == '\'' && (cmdl->opt & SQ))
			cmdl->opt &= ~(SQ);
		else if (cmdl->line.str[i] == '"' && (cmdl->opt & DQ))
			if (i == 0 || cmdl->line.str[i - 1] != '\\')
				cmdl->opt &= ~(DQ);
	}
}

int			check_quote(t_cmdl *cmdl)
{
	count_quote(cmdl);
	if ((cmdl->opt & (SQ | DQ)))
	{
		print(cmdl, " ");
		cmdl->opt & SQ ? write(1, "\nquote> ", 8) : write(1, "\ndquote> ", 9);
		cmdl->line.cur = cmdl->opt & SQ ? 8 : 9;
		cmdl->line.pr = cmdl->opt & SQ ? 8 : 9;
		return (1);
	}
	return (0);
}
