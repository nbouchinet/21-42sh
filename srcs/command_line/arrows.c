/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 18:01:33 by khabbar           #+#    #+#             */
/*   Updated: 2017/08/23 11:25:50 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		arrow_rigth(t_win *win, char *cmd, char buf[])
{
	(void)buf;
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

void		arrow_left(t_win *win, char *cmd, char buf[])
{
	int		i;

	(void)buf;
	(void)cmd;
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

void 		arrows(t_win *win, char *cmd, char buf[])
{
	int						i;
	static const t_arrow	arr[8] = {{27, 91, 68, 0,&arrow_left},
	{27, 91, 67, 0,&arrow_rigth}, {27, 91, 72, 0, &home},
	{27, 91, 70, 0, &end}, {27, 27, 91, 68, &opt_left},
	{27, 27, 91, 67, &opt_right}, {27, 27, 91, 65, &up_dwn},
	{27, 27, 91, 66, &up_dwn}};

	i = -1;
	while (++i < 8)
		if (buf[0] == arr[i].a && buf[1] == arr[i].b && buf[2] == arr[i].c &&
		buf[3] == arr[i].d)
		{
			arr[i].f(win, cmd, buf);
			return ;
		}
}
