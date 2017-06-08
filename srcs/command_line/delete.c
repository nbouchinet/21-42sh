/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 18:17:30 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/24 13:29:15 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int	g_loop;

void 	del_his(char **cmd, t_win *win, t_his **his)
{
	int 	i;
	int		j;

	if (win->cur == win->pr)
		return ;
	arrow_left(win);
	i = win->cur - win->pr - 1;
	j = i + (*his)->len + 5;
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	while (i < j)
	{
		write (1, " ", 1);
		i += 1;
	}
	i = win->cur - win->pr - 1;
	while ((*cmd)[++i])
		(*cmd)[i] = (*cmd)[i + 1];
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	ft_putstr("': ");
	findstr(his, *cmd);
	ft_putstr((*his)->cmdl);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
}

void		del(char **cmd, t_win *win, t_his **his)
{
	int		i;

	if (win->sh)
	{
		del_his(cmd, win, his);
		return ;
	}
	if (win->cur == win->pr)
		return ;
	arrow_left(win);
	win->cpy_b -= win->cpy_b != -1 ? 1 : 0;
	i = win->cur - win->pr - 1;
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	(*cmd) ? del_all(*cmd, win) : 0;
	while ((*cmd)[++i])
		(*cmd)[i] = (*cmd)[i + 1];
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	write(1, (*cmd) + win->cur - win->pr, ft_strlen((*cmd) + win->cur - win->pr));
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
}

void        del_all(char *cmd, t_win *win)
{
	int     i;
	int		j;

	i = win->cur - win->pr - 1;
	j = ft_strlen(cmd);
	while (++i < j)
		write (1, " ", 1);
}

void		init_var(t_win **win)
{
	(*win)->cur = 3;
	(*win)->pr = 3;
	(*win)->cpy_b = -1;
	(*win)->cpy_e = -1;
	(*win)->ccp = 0;
	(*win)->copy = NULL;
	(*win)->quote = 0;
	(*win)->sh = 0;
	(*win)->ctrld = 0;
	(*win)->hd = NULL;
	g_loop = 1;
	print_prompt((*win)->lstenv);
}
