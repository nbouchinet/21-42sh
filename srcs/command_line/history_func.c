/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 14:17:29 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/30 17:52:09 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		lst_len(t_his *his)
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

void	catcmd(t_win *win, char **cmd)
{
	t_hdoc	*hd;
	char	*save;
	int		i;
	int		j;

	i = -1;
	hd = win->hd;
	while (hd)
	{
		while ((*cmd)[++i] != '<')
			;
		i += ((*cmd)[i + 2] == ' ' ? 3 : 2);
		save = ft_strdup((*cmd) + i);
		(*cmd)[i] = 0;
		(*cmd) = ft_strjoinf((*cmd), hd->fd, 1);
		j = -1;
		while (save[++j] && save[j] != ' ' && save[j] != '<' && save[j] != '>'
				&& save[j] != ';' && save[j] != '|' && save[j] != '&')
			;
		(*cmd) = ft_strjoinf((*cmd), (save + j), 1);
		free(save);
		hd = hd->next;
	}
	del_hd(&win->hd);
}

void	del_hd(t_hdoc **hd)
{
	t_hdoc		*tmp;
	t_hdoc		*save;

	tmp = *hd;
	while (tmp)
	{
		save = tmp->next;
		tmp->fd ? ft_strdel(&tmp->fd) : 0;
		tmp->hstring ? ft_strdel(&tmp->hstring) : 0;
		tmp ? free(tmp) : 0;
		tmp = save;
	}
	*hd = NULL;
}
