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

static void	edit_copy(char **cmd, t_win *win)
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

static void     paste(char **cmd, t_win *win)
{
    int		i;
	char	*tmp;

	tmp = NULL;
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	(*cmd) ? del_all(*cmd, win) : 0;
	i = ft_strlen((*cmd)) + 1;
	tmp = ft_strjoinf(win->copy, ft_strsub((*cmd), win->cur - win->pr, ft_strlen((*cmd))), 2);
	edit_copy(cmd, win);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	write(1, tmp, ft_strlen(tmp));
	free(tmp);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	if (win->cur % win->co == 0)
		tputs(tgetstr("do", NULL), 1, ft_putchar);
    win->cpy_b = -1;
    win->cpy_e = -1;
	win->ccp = 0;
}

static void		cut_elem(t_win *win, char **cmd, int i)
{
	if (win->cur == 3)
		return ;
	while (i--)
        del(cmd, win, NULL);
}

static void		swap(char **cmd, t_win *win)
{
	int		tmp;

	tmp = win->cpy_b;
	win->cpy_b = win->cpy_e;
	win->cpy_e = tmp;
	while (win->cur - win->pr < win->cpy_e)
		arrow_rigth(win, *cmd);
}

void        ccp(char **cmd, char buf[], t_win *win)
{
	int		i;

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
	win->copy ? ft_free(NULL, &win->copy) : 0;
	if ((CUT || CPY) && win->cpy_b == -1 && win->cpy_e == -1)
		win->cpy_b = win->cur - win->pr ;
	else if ((CUT || CPY) && win->cpy_b != -1 && win->cpy_e == -1)
		win->cpy_e = win->cur - win->pr;
	if (win->cpy_e == -1)
		return ;
	if (win->cpy_b > win->cpy_e)
		swap(cmd, win);
	i = win->cpy_e - win->cpy_b;
	win->copy = ft_strsub(*cmd, win->cpy_b, i);
	CUT ? cut_elem(win, cmd, i) : 0;
}
