/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ccp_paste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 17:39:43 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/13 09:30:03 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	edit_cmdl(t_cmdl *cmdl, int len_cpy, int len_str, int i)
{
	char	*tmp;
	int		j;

	j = -1;
	while ((len_str = ft_strlen(cmdl->line.str)) + len_cpy >= cmdl->line.len)
		remalloc_cmdl(&cmdl->line, len_str);
	if (cmdl->line.str[cmdl->line.cur - cmdl->line.pr] == 0)
	{
		cmdl->line.str = ft_strcat(cmdl->line.str, cmdl->ccp.cpy);
		cmdl->line.cur += len_cpy;
	}
	else
	{
		tmp = ft_strdup(cmdl->line.str + (cmdl->line.cur - cmdl->line.pr));
		while (cmdl->ccp.cpy[++i])
			cmdl->line.str[cmdl->line.cur++ - cmdl->line.pr] = cmdl->ccp.cpy[i];
		i = cmdl->line.cur - cmdl->line.pr;
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		while (tmp[++j])
			cmdl->line.str[cmdl->line.cur++ - cmdl->line.pr] = tmp[j];
		write(1, cmdl->line.str + i, ft_strlen(cmdl->line.str + i));
		cmdl->line.cur -= (cmdl->line.cur - cmdl->line.pr) - i;
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
		tmp ? free(tmp) : 0;
	}
}

int			paste(t_cmdl *cmdl, int len_cpy)
{
	if ((int)ft_strlen(cmdl->line.str) + cmdl->line.pr + len_cpy >=
	cmdl->line.co * cmdl->line.li - (cmdl->line.co - 1))
		return (beep());
	write(1, cmdl->ccp.cpy, len_cpy);
	edit_cmdl(cmdl, len_cpy, 0, -1);
	if (cmdl->line.cur % cmdl->line.co == 0)
		tputs(tgetstr("do", NULL), 1, ft_putchar);
	cmdl->ccp.start = -1;
	cmdl->ccp.end = -1;
	cmdl->ccp.ccp = 0;
	return (1);
}
