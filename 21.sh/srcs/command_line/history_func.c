/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 14:17:29 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/18 14:17:50 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

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

void    catcmd(char **cmd, t_win *win)
{
	int		i;
	int		j;
	t_hdoc	*hd;
	char	*tmp;

	i = -1;
	hd = win->hd;
	while (hd)
	{
		if (hd->hdoc)
		{
			while ((*cmd)[++i] && (*cmd)[i] != '<')
				;
			j = i + 1;
			while ((*cmd)[++j] == ' ')
				;
			while ((*cmd)[++j] && (*cmd)[j] != ' ')
				;
			tmp = ft_strdup((*cmd) + j);
			(*cmd)[i] = 0;
			(*cmd) = ft_strjoinf((*cmd), ft_strjoinf(hd->hdoc, tmp, 3), 3);
			hd->hdoc = NULL;
		}
		hd = hd->next;
	}
	del_hd(win->hd);
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