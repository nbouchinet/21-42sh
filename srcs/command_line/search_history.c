/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:01:47 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/24 13:29:51 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int g_loop;

void	search_history(char **cmd, t_win **win)
{
	if ((*cmd))
	{
		free(*cmd);
		*cmd = NULL;
	}
	while ((*win)->cur--)
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	write(1, "  ", 2);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	ft_putstr("(reverse-i-search)`");
	(*win)->pr = ft_strlen("(reverse-i-search)`");
	(*win)->cur = 19;
	ft_putstr("': ");
	tputs(tgetstr("le", NULL), 1, ft_putchar);
	tputs(tgetstr("le", NULL), 1, ft_putchar);
	tputs(tgetstr("le", NULL), 1, ft_putchar);
	(*win)->sh = 1;
}

void	findstr(t_his **his, char *cmd)
{
	while ((*his) && (*his)->next)
		(*his) = (*his)->next;
	while ((*his) && (*his)->prev)
		if (ft_strstr((*his)->cmdl, cmd))
			break ;
		else
			(*his) = (*his)->prev;
}

void	print_search(char **cmd, char buf[], t_his **his, t_win *win)
{
	size_t	i;

	i = win->cur - win->pr;
	(*cmd) = ft_strjoinf((*cmd), buf, 1);
	findstr(his, *cmd);
	if (ft_strstr((*his)->cmdl, (*cmd)))
	{
		win->cur += 1;
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		while (i++ < win->cur - win->pr + (*his)->len + 4)
			write(1, " ", 1);
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		ft_printf("%c%@ %@", (*cmd)[win->cur - win->pr - 1], "':", (*his)->cmdl);
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		win->cur % win->co == 0 ? tputs(tgetstr("do", NULL), 1, ft_putchar) : 0;
	}
	else
	{
		(*cmd)[ft_strlen((*cmd)) - 1] = 0;
		beep();
	}
	win->sh = 1;
}

void	exit_sh_mode(t_win *win, t_his **his, char **cmd, char buf[])
{
	int		i;
	int		j;

	if (!(ARR_L || ARR_R) || !(*cmd))
	{
		i = 19;
		while (i--)
			tputs(tgetstr("le", NULL), 1, ft_putchar);
		ft_putstr("$> ");
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		while (++i < 21)
			write(1, " ", 1);
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
		return ;
	}
	i = -1;
	j = (*cmd) ? ft_strlen((*cmd)) + (*his)->len + 23 : win->pr + 2;
	while (win->cur > -1)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		win->cur -= 1;
	}
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	while (++i < j)
		write(1, " ", 1);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	write(1, "$> ", 3);
	win->pr = 3;
	win->sh = 0;
	findstr(his, *cmd);
	ft_free(NULL, cmd);
	(*cmd) = (*his)->cmdl;
	ft_putstr((*cmd));
	win->cur = ft_strlen(*cmd) + 3;
}

void	e(t_win **win, t_his **his, char **cmd, char **save)
{
	char	buf[3];

	buf[0] = 27;
	buf[1] = 91;
	buf[2] = 68;

	exit_sh_mode(*win, his, cmd, buf);
	check_line(save, cmd, win, buf);
}
