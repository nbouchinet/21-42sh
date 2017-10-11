/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 00:24:30 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/11 10:14:55 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		engage_heredoc(t_tok **stop)
{
	int		p[2];
	t_cmdl	*cmdl;

	cmdl = *cmdl_slg();
	init_cmdl();
	cmdl->opt |= CHD;
	if (pipe(p) == -1)
		return (fd_printf(2, "heredoc: pipe error\n"));
	cmdl->line.pr = write(1, "heredoc> ", 9);
	cmdl->line.cur = 9;
	if (hd_loop(stop, cmdl, p, -1) == -1)
		return (-1);
	close(p[1]);
	return (p[0]);
}

void			creat_file(t_tok **lst)
{
	int		fd;

	if (!io_number((*lst)->n->str))
		if ((fd = open((*lst)->n->str, ((*lst)->type == RRDIR ? O_APPEND :
		O_TRUNC) | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))
		!= -1)
			close(fd);
}

int				heredoc(t_tok **lst)
{
	t_tok	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == BBDIR)
		{
			if (tmp->n && tmp->n->type == WORD)
			{
				if ((tmp->n->hd = engage_heredoc(&tmp->n)) == -1)
					return (ft_errormsg(NULL, NULL, ""));
				next_hd(&tmp->n);
			}
			else
				return (-1);
		}
		else if ((tmp->type & (RDIR | RRDIR)))
			creat_file(&tmp);
		tmp = tmp->n;
	}
	return (0);
}
