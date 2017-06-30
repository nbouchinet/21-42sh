/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:49:33 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/30 17:54:43 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			mode_on(t_win **win)
{
	(*win)->term.c_lflag &= ~(ICANON);
	(*win)->term.c_lflag &= ~(ECHO);
	// (*win)->term.c_cc[VMIN] = 1;
	// (*win)->term.c_cc[VTIME] = 0;
	(*win)->term.c_cc[VMIN] = 0;
	(*win)->term.c_cc[VTIME] = 1;
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
	write(1, "Bye\n", 4);
	// free win->hd win->his;
	*win = NULL;
	return (0);
}

int			set_shell(t_win **win)
{
	char			*shl_name;

	tputs(tgetstr("nam", NULL), 1, ft_putchar);
	if (((*win) = (t_win*)malloc(sizeof(t_win))) == NULL)
		return (1);
	if ((shl_name = getenv("TERM")) == NULL)
		shl_name = "xterm-256color";
	if (tgetent(0, shl_name) == ERR)
		return (fd_printf(2, "tgetent: ERROR\n"));
	if (tcgetattr(1, &(*win)->term) == -1)
		return (fd_printf(2, "tcgetattr: ERROR\n"));
	if (mode_on(win) != 0)
		return (1);
	return (0);
}
