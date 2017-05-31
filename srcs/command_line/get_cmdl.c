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

static void print(char **cmd, char buf[], t_win *win)
{
	char	*tmp;
	char	*temp;

	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	del_all(*cmd, win);
	tmp = ft_strjoinf(buf, ft_strsub((*cmd), win->cur - win->pr,
	ft_strlen((*cmd)) - (win->cur - win->pr)), 2);
	if (!(*cmd) || (*cmd)[win->cur - win->pr] == 0)
		(*cmd) = ft_strjoinf((*cmd), buf, 1);
	else if ((temp = (*cmd)))
	{
		(*cmd) = ft_strjoinf(ft_strjoinf(ft_strsub((*cmd), 0, win->cur -
		win->pr), buf, 1), ft_strsub((*cmd), win->cur - win->pr,
		ft_strlen((*cmd))), 3);
		free(temp);
	}
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	write(1, tmp, ft_strlen(tmp));
	(*cmd) ? free(tmp) : 0;
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	tputs(tgetstr("nd", NULL), 1, ft_putchar);
	win->cur += 1;
	if (win->cur % win->co == 0)
		tputs(tgetstr("do", NULL), 1, ft_putchar);
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
		(!(*win)->hd) ? get_here_string(save, win) : heredoc(cmd, win);
	!(*win)->hd && !(*win)->quote ? (*win)->pr = 3 : 0;
	(*save) && !(*win)->hd && !(*win)->quote ? handle_pipe_and_or(save, win) : 0;
	ft_memset((*cmd), 0, ft_strlen(*cmd));
	(*win)->sh = 0;
}

static void		exit_get_cndl(char **cmd, t_win **win, char *save, char buf[])
{
	(*cmd) = save && save[0] ? ft_strjoinf(save, (*cmd), 3) : NULL;
	save_history(*win, cmd, &(*win)->his);
	if ((*cmd) && !(*win)->hd)
		while ((*cmd)[(*win)->cur - (*win)->pr])
			arrow_rigth(*win, (*cmd));
	g_loop = EOT ? 0 : write(1, "\n", 1);
	(*win)->ctrld = EOT ? 1 : 0;
	(*cmd) ? (*cmd) = ft_strtrimf((*cmd)) : 0;
}

void        get_cmdl(char **cmd, t_win **win, char *save, char **env)
{
	char    buf[6];

	init_var(win);
	while (g_loop)
	{
		if (cmdl_signal(cmd, save, win) == 1)
			return ;
		g_loop == 4 ? winsize(win, &save, cmd) : 0;
		ft_memset(buf, '\0', 6);
		read(0, buf, 6);
		if (PRINT)
			!(*win)->sh ? print(cmd, buf, *win) : print_search(cmd, buf,
			&(*win)->his, *win);
		if (MOVE)
			!(*win)->sh ? arrows(*win, *cmd, buf) :
			exit_sh_mode(*win, &(*win)->his, cmd, buf);
		COMP ? completion(win, cmd,   env) : 0;
		DEL && (*cmd) ? del(cmd, *win, &(*win)->his) : 0;
		CCP ? ccp(cmd, buf, *win) : 0;
		!(*win)->sh && UD ? move_history(&(*win)->his, cmd, buf[2], *win) : 0;
		OPT_S && !(*win)->sh ? search_history(cmd, win) : 0;
 		if (RETURN || EOT)
			!(*win)->sh ? check_line(&save, cmd, win, buf) :
			e(win, &(*win)->his, cmd, &save);
	}
	exit_get_cndl(cmd, win, save, buf);
}

// char			*get_path(char **str)
// {
// 	char		*path;
// 	char		*temp;
// 	int			i;
// 	int			save;

// 	save = 0;
// 	i = -1;
// 	while ((*str)[++i])
// 		if ((*str)[i] == '/')
// 			save = i;
// 	if ((*str)[save] == '/')
// 	{
// 		path = ft_strsub((*str), 0, save);
// 		if ((*str)[save + 1])
// 		{
// 			temp = (*str);
// 			(*str) = ft_strsub((*str), save + 1, ft_strlen((*str) + save));
// 			free(temp);
// 		}
// 		else
// 			(*str)[0] = 0;
// 		// (*str)[save + 1] != 0 ? (*str) = ft_strsub((*str), save + 1, ft_strlen((*str) + save)) : 0;
// 	}
// 	else
// 		path = ft_strdup(".");
// 	return (path);
// }
