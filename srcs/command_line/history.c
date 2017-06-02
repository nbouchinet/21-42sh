/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 17:42:31 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/24 13:29:35 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void    del_first(t_his **his)
{
	t_his   *tmp;

	tmp = *his;
	while (tmp->prev)
		tmp = tmp->prev;
	free(tmp->cmdl);
	tmp = tmp->next;
	free(tmp->prev);
	tmp->prev = NULL;
}

static void		first_link(char *cmd, t_his **his)
{
	t_his	*tmp;

	tmp = (t_his *)malloc(sizeof(t_his));
	tmp->cmdl = ft_strdup(cmd);
	tmp->len = ft_strlen(cmd) + 1;
	tmp->prev = NULL;
	tmp->next = (*his);
	(*his)->prev = tmp;
}

static void		get_max_len(t_his **his)
{
	t_his	*tmp;
	size_t	len;

	tmp = *his;
	while (tmp->prev)
		tmp = tmp->prev;
	len = ft_strlen(tmp->cmdl);
	while (tmp->next)
	{
		len = len > ft_strlen(tmp->cmdl) ? len : ft_strlen(tmp->cmdl);
		tmp = tmp->next;
	}
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp->next)
	{
		tmp->len = len;
		tmp = tmp->next;
	}
}

static int		call_first_link(t_win *win, char **cmd, t_his **his)
{
	first_link((*cmd), his);
	win->hd ? catcmd(win, cmd) : 0;
	ft_streplace(&(*his)->cmdl, 127, '\n');
	return (0);
}

void        	save_history(t_win *win, char **cmd, t_his **his)
{
	t_his	*tmp;

	if (!(*cmd) || !(*cmd)[0])
		return ;
	if (!(*his)->next && !(*his)->prev)
	{
		call_first_link(win, cmd, his);
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
	ft_streplace(&(*his)->cmdl, 127, '\n');
	win->hd ? catcmd(win, cmd) : 0;
	get_max_len(his);
	lst_len(*his) >= 31 ? del_first(his) : 0;
}
