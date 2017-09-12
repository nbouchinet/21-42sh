/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 18:06:32 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/11 20:06:34 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void count_quote(t_cmdl *cmdl)
{
	int		i;

	i = -1;
	while (cmdl->line.str[++i])
	{
		if (cmdl->line.str[i] == '\'' && (!(cmdl->opt & (CSQ | CDQ))))
			cmdl->opt |= CSQ;
		else if (cmdl->line.str[i] == '"' && (!(cmdl->opt & (CSQ | CDQ))))
			cmdl->opt |= (i == 0 || cmdl->line.str[i - 1] != '\\' ? CDQ :
			              cmdl->opt);
		else if (cmdl->line.str[i] == '\'' && (cmdl->opt & CSQ))
			cmdl->opt &= ~(CSQ);
		else if (cmdl->line.str[i] == '"' && (cmdl->opt & CDQ))
			if (i == 0 || cmdl->line.str[i - 1] != '\\')
				cmdl->opt &= ~(CDQ);
	}
}

int			check_quote(t_cmdl *cmdl)
{
	count_quote(cmdl);
	if ((cmdl->opt & (CSQ | CDQ)))
	{
		print(cmdl, " ");
		cmdl->opt & CSQ ? write(1, "\nquote> ", 8) : write(1, "\ndquote> ", 9);
		cmdl->line.cur = cmdl->opt & CSQ ? 8 : 9;
		cmdl->line.pr = cmdl->opt & CSQ ? 8 : 9;
		return (1);
	}
	return (0);
}
