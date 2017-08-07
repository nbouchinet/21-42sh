/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 17:51:25 by khabbar           #+#    #+#             */
/*   Updated: 2017/08/04 14:38:14 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int g_loop;

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
		arrow_left(win, NULL, NULL);
	return (1);
}

static void		exit_get_cmdl(char **cmd, t_win **win, char **save)
{
	(*cmd) = (*save) && (*save)[0] ?
		ft_strtrimf(ft_strjoinf((*save), (*cmd), 3)) : NULL;
	save_history(*win, cmd, &(*win)->his);
	(*cmd) ? end(*win, *cmd, NULL) : 0;
	!(*win)->ctrld ? write(1, "\n", 1) : 0;
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
		if ((RETURN || EOT) && check_cmdl(&save, cmd, win, buf))
			break ;
	}
	exit_get_cmdl(cmd, win, &save);
}
