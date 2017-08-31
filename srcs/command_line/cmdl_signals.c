/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdl_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 11:01:02 by khabbar           #+#    #+#             */
//   Updated: 2017/08/31 10:44:02 by nbouchin         ###   ########.fr       //
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

void		cmdl_wins(int signal)
{
	if (signal == 28)
		g_loop = 4;
}

void		cmdl_ctrc(int signal)
{
	tcsetpgrp (g_shell_terminal, g_shell_pgid);
	if (signal == 2)
	{
		// ft_putendl("PASS");
		if (signal == SIGINT)
			g_loop = 3;
	}

void	ctrl_z(int signal)
{
	if (signal == SIGTSTP)
	{
		job_control(NULL, NULL, SUS);
		g_loop = 3;
	}
}

void		canon_mode(int signal)
{
	if (signal == 21)
		g_loop = 6;
}

int				cmdl_signal(char **cmd, char *save, t_win **win)
{
	signal(SIGINT, cmdl_ctrc);
	signal(21, canon_mode);
	signal(28, cmdl_wins);
	signal(SIGTSTP, ctrl_z);
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
