/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:09:42 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/10 18:53:06 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	comp_mode(t_cmdl *cmdl, int save)
{
	cmdl->line.cur = write(1, cmdl->line.str, ft_strlen(cmdl->line.str)) +
	cmdl->line.pr;
	while (cmdl->line.cur > save)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		--cmdl->line.cur;
	}
	display_comp(cmdl, &cmdl->comp, cmdl->offset);
}

static void	his_mode(t_cmdl *cmdl)
{
	char	*match;

	match = NULL;
	cmdl->opt &= ~(CHIS_S);
	if (cmdl->line.str[0])
	{
		ft_memset(cmdl->line.str, 0, ft_strlen(cmdl->line.str));
		match = findcmdl(cmdl->line.str, cmdl->line.buf, 2)->cmdl;
		while ((int)ft_strlen(match) > cmdl->line.len)
			remalloc_cmdl(&cmdl->line);
		ft_strcpy(cmdl->line.str, match);
		write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
		cmdl->line.cur = ft_strlen(cmdl->line.str) + cmdl->line.pr;
		findcmdl(NULL, NULL, 1);
	}
	else
	{
		cmdl->line.pr = 3;
		cmdl->line.cur = 3;
	}
}

int			ctrl_l(t_cmdl *cmdl)
{
	int		save;

	save = cmdl->line.cur;
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	print_prompt();
	if (cmdl->opt & CHIS_S)
		his_mode(cmdl);
	else if (cmdl->opt & CCOMP)
		comp_mode(cmdl, save);
	else if (cmdl->line.str[0])
	{
		cmdl->ccp.start = -1;
		cmdl->ccp.end = -1;
		if (cmdl->ccp.cpy)
			ft_strdel(&cmdl->ccp.cpy);
		write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
		cmdl->line.cur = ft_strlen(cmdl->line.str) + cmdl->line.pr;
	}
	return (1);
}
