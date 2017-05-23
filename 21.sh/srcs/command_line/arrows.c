/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 18:01:33 by khabbar           #+#    #+#             */
/*   Updated: 2017/04/30 18:01:35 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void	arrow_rigth(t_win *win, char *cmd)
{
	if (!cmd || !cmd[win->cur - win->pr])
	{
		beep();
		return ;
	}
	win->cur += 1;
	if (win->cur % win->co == 0)
		tputs(tgetstr("do", NULL), 1, ft_putchar);
	else
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
}

void	arrow_left(t_win *win)
{
	int		i;

	if (win->cur == win->pr)
	{
		beep();
		return ;
	}
	i = -1; 
	if (win->cur % win->co == 0)
	{
		while (++i < win->co)
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	win->cur -= 1;
}

static void up_dwn(t_win *win, char *cmd, char buf[])
{
	int		tmp;
	int		len;

	tmp = win->co + 1;
	len = ft_strlen(cmd);
	if (OPT_D && win->cur + win->co - win->pr >= len && len >= win->co)
		while (cmd[win->cur - win->pr])
			arrow_rigth(win, cmd);
	else if (OPT_U && win->cur >= win->co)
		while (--tmp)
			arrow_left(win);
	else if (OPT_D && len >= win->co - win->pr)
		while (--tmp)
			arrow_rigth(win, cmd);
}

void        arrows(t_win *win, char *cmd, char buf[])
{
	if (ARR_L || ARR_R)
		ARR_L ? arrow_left(win) : arrow_rigth(win, cmd);
	else if (HOME && cmd)
		while (win->cur > 3)
			arrow_left(win);
	else if (END && cmd)
		while (cmd[win->cur - win->pr])
			arrow_rigth(win, cmd);
	else if (OPT_L && cmd)
	{
		while (cmd[win->cur - win->pr] != ' ' && win->cur > win->pr)
			arrow_left(win);
		while (cmd[win->cur - win->pr] == ' ' && win->cur > win->pr)
			arrow_left(win);
	}
	else if (OPT_R && cmd)
	{
		while (cmd[win->cur - win->pr] != ' ' && cmd[win->cur - win->pr] != 0)
			arrow_rigth(win, cmd);
		while (cmd[win->cur - win->pr] == ' ' && cmd[win->cur - win->pr] != 0)
			arrow_rigth(win, cmd);
	}
	else if (cmd && (OPT_U || OPT_D))
		up_dwn(win, cmd, buf);
}