/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:49:33 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/09 22:18:42 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		save_his_session(t_win **win)
{
	int			fd;
	t_his		*tmp;
	t_his		*save;

	if (!(*win)->his)
		return ;
	while ((*win)->his->prev)
		(*win)->his = (*win)->his->prev;
	tmp = (*win)->his;
	if ((fd = open(".42sh_history", O_RDWR | O_APPEND | O_CREAT, 0700)) == -1)
			fd_printf(2, "Could no write history list to history file\n");
	while (tmp && fd != -1)
	{
		save = tmp->next;
		!tmp->add ? ft_putendl_fd(tmp->cmdl, fd) : 0;
		ft_strdel(&tmp->cmdl);
		free(tmp);
		tmp = save;
	}
	fd != -1 ? close(fd) : 0;
}

int				mode_on(t_win **win)
{
	(*win)->term.c_lflag &= ~(ICANON);
	(*win)->term.c_lflag &= ~(ECHO);
	(*win)->term.c_cc[VMIN] = 0;
	(*win)->term.c_cc[VTIME] = 0;
	// (*win)->term.c_cc[VMIN] = 0;
	// (*win)->term.c_cc[VTIME] = 1;
	// write(2, "loooooooooooooooool\n", 42);
	while (tcgetpgrp (g_shell_terminal) != (g_shell_pgid = getpgrp ()))
		kill (- g_shell_pgid, SIGTTIN);
	tcsetpgrp(g_shell_terminal, g_shell_pgid);
	if (tcsetattr(1, TCSADRAIN, &(*win)->term) == -1)
		return (fd_printf(2, "set-shell: tcsetattr: ERROR\n"));
	return (0);
}

int			mode_off(t_win **win)
{
	(*win)->term.c_lflag |= ICANON;
	(*win)->term.c_lflag |= ECHO;
	if (tcsetattr(1, TCSADRAIN, &(*win)->term) == -1)
		return (fd_printf(2, "unset-shell: tcsetattr: ERROR\n"));
	return (0);
}

int			unset_shell(t_win **win)
{
	if (mode_off(win) != 0)
		return (-1);
	tputs(tgetstr("am", NULL), 1, ft_putchar);
	save_his_session(win);
	(*win)->hd ? del_hd(&(*win)->hd) : 0;
	write(1, "Bye\n", 4);
	return (0);
}

t_win		*win_sgt(void)
{
	static t_win *win = NULL;

	if (!win)
	{
		if ((win = (t_win*)malloc(sizeof(t_win))) == NULL)
			exit(fd_printf(2, "malloc error\n"));
		return (win);
	}
	return (win);
}

int			set_shell(t_win **win)
{
	char			*shl_name;

	signal (SIGCHLD, SIG_DFL);
	g_shell_terminal = STDIN_FILENO;
	g_shell_is_interactive = isatty(g_shell_terminal);
	tputs(tgetstr("nam", NULL), 1, ft_putchar);
	*win = win_sgt();
	if (g_shell_is_interactive)
	{
		while (tcgetpgrp(g_shell_terminal) != (g_shell_pgid = getpgrp()))
			kill(- g_shell_pgid, SIGTTIN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGWINCH, SIG_IGN);
		signal(SIGCHLD, SIG_DFL);
		signal(SIGINT, cmdl_ctrc);
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
	}
	if ((shl_name = getenv("TERM")) == NULL)
		shl_name = "xterm-256color";
	if (tgetent(0, shl_name) == ERR)
		return (fd_printf(2, "tgetent: ERROR\n"));
	if (tcgetattr(1, &(*win)->term) == -1)
		return (1);
	if (mode_on(win) != 0)
		return (1);
	return (0);
}
