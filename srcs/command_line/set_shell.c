/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:55:35 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/17 13:12:54 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				get_win_data(t_cmdl *cmdl)
{
	struct winsize	w;

	if (ioctl(0, TIOCGWINSZ, &w) != -1)
	{
		cmdl->line.co = w.ws_col;
		cmdl->line.li = w.ws_row;
		return (0);
	}
	return (1);
}

int				mode_off(t_cmdl *cmdl)
{
	cmdl->term.c_lflag |= ICANON;
	cmdl->term.c_lflag |= ECHO;
	if (tcsetattr(1, TCSADRAIN, &cmdl->term) == -1)
		return (fd_printf(2, "unset_shell: tcsetattr: ERROR\n"));
	return (0);
}

int				mode_on(t_cmdl *cmdl)
{
	cmdl->term.c_lflag &= ~(ICANON);
	cmdl->term.c_lflag &= ~(ECHO);
	cmdl->term.c_cc[VMIN] = 0;
	cmdl->term.c_cc[VTIME] = 1;
	while (tcgetpgrp(g_shell_terminal) != (g_shell_pgid = getpgrp()))
		kill(-g_shell_pgid, SIGTTIN);
	tcsetpgrp(g_shell_terminal, g_shell_pgid);
	if (tcsetattr(1, TCSADRAIN, &cmdl->term) == -1)
		return (fd_printf(2, "set-shell: tcsetattr: ERROR\n"));
	return (0);
}

t_cmdl			*win_sgt(void)
{
	static t_cmdl *win = NULL;

	if (!win)
	{
		if (!(win = (t_cmdl*)malloc(sizeof(t_cmdl))))
			exit(fd_printf(2, "malloc error\n"));
		return (win);
	}
	return (win);
}

int				set_shell(t_cmdl *cmdl)
{
	char		*shl_name;

	signal(SIGCHLD, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	g_shell_terminal = STDIN_FILENO;
	if ((g_shell_is_interactive = isatty(g_shell_terminal)))
	{
		while (tcgetpgrp(g_shell_terminal) != (g_shell_pgid = getpgrp()))
			kill(-g_shell_pgid, SIGTTIN);
		shell_sig();
		if ((shl_name = getenv("TERM")) == NULL)
			shl_name = "xterm-256color";
		if ((tgetent(0, shl_name)) == ERR)
			return (fd_printf(2, "tgetent: ERROR\n"));
		if (tcgetattr(1, &cmdl->term) == -1)
			return (fd_printf(2, "tcgetattr: ERROR\n"));
		if (mode_on(cmdl))
			return (1);
	}
	return (0);
}
