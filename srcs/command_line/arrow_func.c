/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 15:31:24 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/23 15:31:32 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void 		home(t_win *win, char *cmd, char buf[])
{
	(void)buf;
	if (cmd)
		while (win->cur > win->pr)
			arrow_left(win, cmd, buf);
}

void 		end(t_win *win, char *cmd, char buf[])
{
	(void)buf;
	if (cmd)
		while (cmd[win->cur - win->pr])
			arrow_rigth(win, cmd, buf);
}

void 		opt_left(t_win *win, char *cmd, char buf[])
{
	(void)buf;
	if (cmd)
	{
		while (cmd[win->cur - win->pr] != ' ' && win->cur > win->pr)
			arrow_left(win, cmd, buf);
		while (cmd[win->cur - win->pr] == ' ' && win->cur > win->pr)
			arrow_left(win, cmd, buf);
	}
}

void 		opt_right(t_win *win, char *cmd, char buf[])
{
	if (cmd)
	{
		while (cmd[win->cur - win->pr] != ' ' && cmd[win->cur - win->pr] != 0)
			arrow_rigth(win, cmd, buf);
		while (cmd[win->cur - win->pr] == ' ' && cmd[win->cur - win->pr] != 0)
			arrow_rigth(win, cmd, buf);
	}
}

void	up_dwn(t_win *win, char *cmd, char buf[])
{
	int		tmp;
	int		len;

	tmp = win->co + 1;
	len = ft_strlen(cmd);
	if (OPT_D && win->cur + win->co - win->pr >= len && len >= win->co)
		while (cmd[win->cur - win->pr])
			arrow_rigth(win, cmd, buf);
	else if (OPT_U && win->cur >= win->co)
		while (--tmp)
			arrow_left(win, cmd, buf);
	else if (OPT_D && len >= win->co - win->pr)
		while (--tmp)
			arrow_rigth(win, cmd, buf);
}
