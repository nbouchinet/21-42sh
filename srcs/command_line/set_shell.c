/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:55:35 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 13:15:31 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		get_win_data(t_cmdl *cmdl)
{
	struct winsize	w;

	if (ioctl(0, TIOCGWINSZ, &w) == -1)
		return (fd_printf(2, "Error while accesing terminal data\n"));
	cmdl->line.co = w.ws_col;
	cmdl->line.li = w.ws_row;
	return (0);
}

int		unset_shell(t_cmdl *cmdl)
{
	if (mode_off(cmdl))
		return (1);
	tputs(tgetstr("am", NULL), 1, ft_putchar);

	// save l hsitorique de la session et del les listes

	write(1, "Bye\n", 4);
	return (0);
}

int		mode_off(t_cmdl *cmdl)
{
	cmdl->term.c_lflag |= ICANON;
	cmdl->term.c_lflag |= ECHO;
	if (tcsetattr(1, TCSADRAIN, &cmdl->term) == -1)
		return (fd_printf(2, "unset_shell: tcsetattr: ERROR\n"));
	return (0);
}

int		mode_on(t_cmdl *cmdl)
{
	
	cmdl->term.c_lflag &= ~(ICANON);
	cmdl->term.c_lflag &= ~(ECHO);
	cmdl->term.c_cc[VMIN] = 1;
	cmdl->term.c_cc[VTIME] = 0;
	while (tcgetpgrp (g_shell_terminal) != (g_shell_pgid = getpgrp ()))
		kill (- g_shell_pgid, SIGTTIN);
	tcsetpgrp(g_shell_terminal, g_shell_pgid);
	if (tcsetattr(1, TCSADRAIN, &cmdl->term) == -1)
		return (fd_printf(2, "set-shell: tcsetattr: ERROR\n"));
	return (0);
}

t_cmdl		*win_sgt(void)
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

int		set_shell(t_cmdl *cmdl)
{
	char		*shl_name;

	signal (SIGCHLD, SIG_DFL);
	g_shell_terminal = STDIN_FILENO;
	if ((g_shell_is_interactive = isatty(g_shell_terminal)))
	{
		while (tcgetpgrp(g_shell_terminal) != (g_shell_pgid = getpgrp()))
			kill(- g_shell_pgid, SIGTTIN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGWINCH, SIG_IGN);
		signal(SIGCHLD, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		g_shell_pgid = getpid();
		if (setpgid (g_shell_pgid, g_shell_pgid) < 0)
		{
			perror ("Couldn't put the shell in its own process group");
			exit (1);
		}
		tcsetpgrp (g_shell_terminal, g_shell_pgid);
		tcgetattr (g_shell_terminal, &g_shell_tmodes);
		tputs(tgetstr("nam", NULL), 1, ft_putchar);
		//mdl = win_sgt();
	}
	if ((shl_name = getenv("TERM")) == NULL)
		shl_name = "xterm-256color";
	if ((tgetent(0, shl_name)) == ERR)
		return (fd_printf(2, "tgetent: ERROR\n"));
	if (tcgetattr(1, &cmdl->term) == -1)
		return (fd_printf(2, "tcgetattr: ERROR\n"));
	if (mode_on(cmdl))
		return (1);
	return (0);
}
