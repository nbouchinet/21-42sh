/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 17:51:25 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/30 18:01:25 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int g_loop;

static void		move_history(t_his **his, char **cmd, char buf, t_win *win)
{
	char		*tmp;

	tmp = (*cmd);
	win->cpy_b = -1;
	win->cpy_e = -1;
	if ((buf == 65 && !(*his)->prev) || (buf == 66 && !(*his)->next))
		return ;
	while (win->cur > win->pr)
		arrow_left(win);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	del_all(*cmd, win);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	get_history(his, tmp, cmd, buf);
	win->cur += (int)ft_strlen(*cmd);
}

static int		print(char **cmd, char buf[], t_win *win)
{
	char	*tmp;
	char	*save;
	int		i;

	if ((int)ft_strlen((*cmd)) + win->pr >= win->co * win->li - (win->co + 1))
		return (beep());
	i = win->cur - win->pr;
	if (!(*cmd) || !((*cmd)[i]))
		(*cmd) = ft_strjoinf((*cmd), buf, 1);
	else
	{
		tmp = ft_strsub((*cmd), i, ft_strlen((*cmd) + i));
		save = (*cmd);
		(*cmd) = ft_strjoinf(ft_strsub((*cmd), 0, i), buf, 1);
		free(save);
		(*cmd) = ft_strjoinf((*cmd), tmp, 3);
	}
	write(1, (*cmd) + i, ft_strlen((*cmd) + i));
	win->cur += ft_strlen((*cmd) + i);
	!(win->cur % win->co) ? tputs(tgetstr("do", NULL), 1, ft_putchar) : 0;
	while (win->cur - win->pr - 1 > i)
		arrow_left(win);
	return (1);
}

void			check_line(char **save, char **cmd, t_win **win, char buf[])
{
	if ((!(*cmd) || !(*cmd)[0] || EOT) &&
	!(*win)->hd && !(*win)->pao && !(*win)->quote)
	{
		(EOT && (!(*cmd) || !(*cmd)[0])) ? (*win)->ctrld = 1 : 0;
		(!(*cmd) || !(*cmd)[0]) ? g_loop = 0 : 0;
		return ;
	}
	if (!(*win)->hd && check_quotes(cmd, win))
		(*save) = ft_strjoinf((*save), (*cmd), 1);
	if (!(*win)->quote)
		(!(*win)->hd) ? get_here_string(save, win, -1, 0) :
		heredoc(cmd, win, buf);
	if ((*save) && !(*win)->hd && !(*win)->quote)
		handle_pipe_and_or(save, win);
	if ((*save) && !(*win)->hd && !(*win)->quote && !(*win)->pao &&
			(*save)[ft_strlen((*save)) - 1] == '\\')
	{
		write(1, "\n$> ", 4);
		g_loop = 256;
		(*win)->cur = 3;
	}
	ft_memset((*cmd), 0, ft_strlen(*cmd));
	!(*win)->hd && !(*win)->quote && !(*win)->pao ? (*win)->pr = 3 : 0;
	(*win)->sh = 0;
}

static void		exit_get_cmdl(char **cmd, t_win **win, char **save)
{
	(*cmd) = (*save) && (*save)[0] ?
		ft_strtrimf(ft_strjoinf((*save), (*cmd), 3)) : NULL;
	save_history(*win, cmd, &(*win)->his);
	if ((*cmd))
		while ((*cmd)[(*win)->cur - (*win)->pr])
			arrow_rigth(*win, (*cmd));
	write(1, "\n", 1);
	(*win)->copy ? ft_strdel(&(*win)->copy) : 0;
	g_loop = 256;
}

void			get_cmdl(char **cmd, t_win **win, char *save, char buf[])
{
	init_var(win);
	while (g_loop)
	{
		if (cmdl_signal(cmd, save, win) == 1)
			return ;
		ft_memset(buf, '\0', 6);
		read(0, buf, 6);
		if (buf[0] == 12 && !buf[1])
			ctrl_l(win, cmd);
		else if (PRINT)
			!(*win)->sh ? print(cmd, buf, *win) : print_search(cmd, buf,
					&(*win)->his, *win);
		else if (MOVE)
			!(*win)->sh ? arrows(*win, *cmd, buf) :
				exit_sh_mode(*win, &(*win)->his, cmd, buf);
		COMP ? completion(win, cmd) : 0;
		DEL && (*cmd) ? del(cmd, *win, &(*win)->his) : 0;
		CCP && !(*win)->sh ? ccp(cmd, buf, *win) : 0;
		!(*win)->sh && UD ? move_history(&(*win)->his, cmd, buf[2], *win) : 0;
		OPT_S && !(*win)->sh ? search_history(cmd, win) : 0;
		if (RETURN || EOT)
			!(*win)->sh ? check_line(&save, cmd, win, buf) :
				e(win, &(*win)->his, cmd, &save);
	}
	exit_get_cmdl(cmd, win, &save);
}
