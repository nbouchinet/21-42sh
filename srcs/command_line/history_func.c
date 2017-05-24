/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 14:17:29 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/24 13:29:30 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int    lst_len(t_his *his)
{
	t_his	*tmp;
	int		count;

	tmp = his;
	count = 1;
	if (!tmp)
		return (0);
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp->next)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

void    catcmd(t_win *win)
{
	t_hdoc	*hd;

	hd = win->hd;
	win->fd = open(win->hd_path, O_TRUNC);
	win->fd = open(win->hd_path, O_WRONLY);
	while (hd)
	{
		if (hd->hdoc)
		{
			ft_putstr_fd(hd->hdoc, win->fd);
			ft_putchar_fd(127, win->fd);
		}
		hd = hd->next;
	}
	del_hd(win->hd);
	close(win->fd);
}

void	del_hd(t_hdoc *hd)
{
	t_hdoc		*tmp;
	t_hdoc		*save;

	tmp = hd;
	while (tmp)
	{
		save = tmp->next;
		tmp->hstring ? free(tmp->hstring) : 0;
		tmp->hstring = NULL;
		tmp->hdoc ? free(tmp->hdoc) : 0;
		tmp->hdoc = NULL;
		free(tmp);
		tmp = save;
	}
	hd = NULL;
}
