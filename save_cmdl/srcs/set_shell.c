/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:55:35 by khabbar           #+#    #+#             */
/*   Updated: 2017/08/31 17:55:45 by khabbar          ###   ########.fr       */
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

int		mode_off(t_cmdl *cmdl)
{
	cmdl->term.c_lflag |= ICANON;
	cmdl->term.c_lflag |= ECHO;
	if (tcsetattr(1, TCSADRAIN, &cmdl->term) == -1)
		return (fd_printf(2, "unset_shell: tcsetattr: ERROR\n"));
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

int		mode_on(t_cmdl *cmdl)
{
	cmdl->term.c_lflag &= ~(ICANON);
	cmdl->term.c_lflag &= ~(ECHO);
	cmdl->term.c_cc[VMIN] = 1;
	cmdl->term.c_cc[VTIME] = 0;
	if (tcsetattr(1, TCSADRAIN, &cmdl->term) == -1)
		return (fd_printf(2, "set-shell: tcsetattr: ERROR\n"));
	return (0);
}

int		set_shell(t_cmdl *cmdl)
{
	char		*shl_name;

	tputs(tgetstr("nam", NULL), 1, ft_putchar);
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
