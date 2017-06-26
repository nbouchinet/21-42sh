/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 17:51:25 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/24 13:29:20 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int g_loop;

static void        move_history(t_his **his, char **cmd, char buf, t_win *win)
{
    char    *tmp;

    tmp = (*cmd);
	win->cpy_b = -1;
	win->cpy_e = -1;
	if ((buf == 65 && !(*his)->prev) || (buf == 66 && !(*his)->next))
        return ;
	while (win->cur > win->pr)
		arrow_left(win);
	tputs(tgetstr("sc", NULL),1 ,ft_putchar);
	del_all(*cmd, win);
	tputs(tgetstr("rc", NULL),1 ,ft_putchar);
    if (buf == 65)
	{
		if ((*his)->prev && ((*his) = (*his)->prev))
		{
			(*cmd) = ft_strdup((*his)->cmdl);
			free(tmp);
		}
	}
	else if ((*his)->next && ((*his) = (*his)->next))
	{
		free(tmp);
		(*cmd) = ft_strdup((*his)->cmdl);
	}
    ft_putstr(*cmd);
    win->cur += (int)ft_strlen(*cmd);
}

static int print(char **cmd, char buf[], t_win *win)
{
	char	*tmp;
	char	*save;
	int		i;

	if ((int)ft_strlen((*cmd)) + win->pr >= win->co * win->li - (win->co + 1))
		return (beep());
	i = win->cur - win->pr;
	if (!(*cmd) || ((*cmd)[i]) == 0)
		(*cmd) = ft_strjoinf((*cmd), buf, 1);
	else
	{
		tmp = ft_strsub((*cmd), i, ft_strlen((*cmd) + i));
		save = (*cmd);
		(*cmd) = ft_strjoinf(ft_strsub((*cmd), 0, i), buf, 1);
		free(save);
		(*cmd) = ft_strjoinf((*cmd), tmp, 3);
	}
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	write(1, (*cmd) + i, ft_strlen((&(*cmd)[i])));
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	win->cur += 1;
	win->cpy_b != -1 ? win->cpy_b += 1 : 0;
	win->cur % win->co ? tputs(tgetstr("nd", NULL), 1, ft_putchar) : 
	tputs(tgetstr("do", NULL), 1, ft_putchar);
	return (1);
}

void	check_line(char **save, char **cmd, t_win **win, char buf[])
{
	if (!(*cmd) || EOT)
	{
		EOT ? (*win)->ctrld = 1 : 0;
		g_loop = 0;
		return ;
	}
	if (!(*win)->hd && check_quotes(cmd, win) == 1)
		(*save) =  ft_strjoinf((*save), (*cmd), 1);
	if (!(*win)->quote)
		(!(*win)->hd) ? get_here_string(save, win, -1, 0) : heredoc(cmd, win);
	!(*win)->hd && !(*win)->quote ? (*win)->pr = 3 : 0;
	(*save) && !(*win)->hd && !(*win)->quote ? handle_pipe_and_or(save, win) : 0;
	if ((*save) && (*save)[ft_strlen(*save) - 2] == '\\')
	{
		write(1, "\n$> ", 4);
		(*win)->cur = 3;
		g_loop = 1;
	}
	ft_memset((*cmd), 0, ft_strlen(*cmd));
	(*win)->sh = 0;
}

static void		exit_get_cmdl(char **cmd, t_win **win, char *save, char buf[])
{
	(*cmd) = save && save[0] ? ft_strjoinf(save, (*cmd), 3) : NULL;
	save_history(*win, cmd, &(*win)->his);
	if ((*cmd))
		while ((*cmd)[(*win)->cur - (*win)->pr])
			arrow_rigth(*win, (*cmd));
	write(1, "\n", 1);
	g_loop = EOT ? 0 : 256;
	(*win)->ctrld = EOT ? 1 : 0;
	(*cmd) ? (*cmd) = ft_strtrimf((*cmd)) : 0;
}

void        get_cmdl(char **cmd, t_win **win, char *save)
{
	char    buf[6];

	init_var(win);
	while (g_loop)
	{
		if (cmdl_signal(cmd, save, win) == 1)
			return ;
		ft_memset(buf, '\0', 6);
		read(0, buf, 6);
		buf[0] == 12 && !buf[1] ? ctrl_l(win, cmd) : 0;
		if (PRINT)
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
	exit_get_cmdl(cmd, win, save, buf);
}