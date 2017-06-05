/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 15:24:58 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/24 13:29:10 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	edit_cmd(char **cmd, t_win *win)
{
	char	*temp;
	char	*save;

	if (!(*cmd) || (*cmd)[win->cur - win->pr] == 0)
		(*cmd) = ft_strjoinf((*cmd), win->copy, 1);
	else
	{
		temp = ft_strsub((*cmd), win->cur - win->pr, ft_strlen((*cmd)));
		save = (*cmd);
		(*cmd) = ft_strjoinf(ft_strsub((*cmd), 0, win->cur - win->pr), win->copy, 1);
		free(save);
		(*cmd) = ft_strjoinf((*cmd), temp, 3);
	}
}

static int     paste(char **cmd, t_win *win)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	if ((int)ft_strlen((*cmd)) + win->pr + (int)ft_strlen(win->copy)
	>= win->co * win->li - (win->co + 1))
		return (beep());
	ft_putstr(win->copy);
	i = win->cur - win->pr;
	win->cur += ft_strlen(win->copy);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	ft_putstr(&(*cmd)[i]);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	edit_cmd(cmd, win);
	if (win->cur % win->co == 0)
		tputs(tgetstr("do", NULL), 1, ft_putchar);
    win->cpy_b = -1;
    win->cpy_e = -1;
	win->ccp = 0;
	return (1);
}

static void		swap(char **cmd, t_win *win, int j, int i)
{
	int		tmp;

	if (j == 0)
	{
		tmp = win->cpy_b;
		win->cpy_b = win->cpy_e;
		win->cpy_e = tmp;
		while (win->cur - win->pr < win->cpy_e)
			arrow_rigth(win, *cmd);
	}
	else if (j == 1)
	{
		win->cpy_b = -1;
		win->cpy_e = -1; 
	}
	else
	{
		if (win->cur == 3)
			return ;
		while (i--)
        	del(cmd, win, NULL);
	}
}

static void	mark_be(char **cmd, char buf[], t_win *win)
{
	int		i;

	if ((CUT || CPY) && win->cpy_b == -1 && win->cpy_e == -1)
		win->cpy_b = win->cur - win->pr ;
	else if ((CUT || CPY) && win->cpy_b != -1 && win->cpy_e == -1)
		win->cpy_e = win->cur - win->pr;
	if (win->cpy_e == -1)
		return ;
	if (win->cpy_b > (int)ft_strlen(*cmd) + 1)
	{
		swap (cmd, win, 1, 0);
		return ;
	}
	if (win->cpy_b > win->cpy_e)
		swap(cmd, win, 0, 0);
	i = win->cpy_e - win->cpy_b;
	win->copy = ft_strsub(*cmd, win->cpy_b, i);
	CUT ? swap(cmd, win, 2, i) : 0;
}

void        ccp(char **cmd, char buf[], t_win *win)
{

	if (PST && win->copy)
	{
		paste(cmd, win);
		return ;
	}
	if (PST && win->cpy_e == -1)
		return ;
	win->ccp = CUT ? 1 : 2;
	if ((CUT && win->ccp == 2) || (CPY && win->ccp == 1))
		return ;
	win->copy ? ft_strdel(&win->copy) : 0;
	mark_be(cmd, buf, win);
}
