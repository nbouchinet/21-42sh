/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 17:42:31 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/30 17:51:24 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		first_link(t_win *win, char **cmd, t_his **his)
{
	t_his	*tmp;

	(void)win;
	if (!(tmp = (t_his *)malloc(sizeof(t_his))))
		exit(fd_printf(2, "malloc error\n"));
	tmp->cmdl = ft_strdup((*cmd));
	tmp->len = ft_strlen((*cmd)) + 1;
	tmp->prev = NULL;
	tmp->next = (*his);
	(*his)->prev = tmp;
	win->hd ? catcmd(win, cmd) : 0;
	ft_streplace(&tmp->cmdl, 127, ' ');
}

void			save_history(t_win *win, char **cmd, t_his **his)
{
	t_his	*tmp;

	if (!(*cmd) || !(*cmd)[0])
		return ;
	if (!(*his)->next && !(*his)->prev)
	{
		first_link(win, cmd, his);
		return ;
	}
	while ((*his)->next)
		(*his) = (*his)->next;
	tmp = (*his);
	(*his) = (*his)->prev;
	if (!((*his)->next = (t_his *)malloc(sizeof(t_his))))
		exit(fd_printf(2, "save-hisroty: malloc error\n"));
	(*his)->next->cmdl = ft_strdup((*cmd));
	(*his)->next->prev = (*his);
	(*his)->next->next = tmp;
	(*his) = (*his)->next;
	(*his)->next->prev = (*his);
	(*his) = (*his)->next;
	ft_streplace(&(*his)->cmdl, 127, ' ');
	win->hd ? catcmd(win, cmd) : 0;
}
