/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdl_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 11:01:02 by khabbar           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2017/08/22 17:58:38 by nbouchin         ###   ########.fr       */
=======
/*   Updated: 2017/08/22 21:41:40 by zadrien          ###   ########.fr       */
>>>>>>> 0a08fd6c1c7f3c39df8774549ac5aef5c91c7464
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int g_loop;

static void		winsize(t_win **win, char **save, char **cmd)
{
	char	*line;

	line = (*save) ? (*save) : (*cmd);
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	get_win_data(win);
	print_prompt(win);
	write(1, line, ft_strlen(line));
}

static void		cmdl_wins(int signal)
{
	if (signal == 28)
		g_loop = 4;
}

static void		cmdl_ctrc(int signal)
{
	ft_putendl_fd("NTMMMMM", 2);
	tcsetpgrp (g_shell_terminal, g_shell_pgid);
	if (signal == 2)
	{
		ft_putendl("PASS");
		g_loop = 3;
	}
}

void	ctrl_z(int signal)
{
	if (signal == SIGTSTP)
	{
		job_control(NULL, NULL, SUS);
		g_loop = 3;
	}
}

static void		canon_mode(int signal)
{
	if (signal == 21)
		g_loop = 6;
}

int				cmdl_signal(char **cmd, char *save, t_win **win)
{
	signal(2, cmdl_ctrc);
	signal(21, canon_mode);
	signal(28, cmdl_wins);
	signal(18, ctrl_z);
	g_loop == 4 ? winsize(win, &save, cmd) : 0;
	g_loop == 6 ? mode_on(win) : 0;
	g_loop == 6 ? print_prompt(win) : 0;
	if (g_loop == 3)
	{
		(*cmd) ? end(*win, *cmd, NULL) : 0;
		(*cmd) ? free((*cmd)) : 0;
		save ? ft_strdel(&save) : 0;
		(*win)->hd ? del_hd(&(*win)->hd) : 0;
		(*cmd) = NULL;
		write(1, "\n", 1);
		g_loop = 256;
		return (1);
	}
	g_loop = 256;
	return (0);
}
