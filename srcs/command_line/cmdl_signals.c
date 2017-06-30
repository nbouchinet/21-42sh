/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdl_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 11:01:02 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/30 17:29:01 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int g_loop;

static void		cmdl_wins(int signal)
{
	if (signal == 28)
		g_loop = 4;
}

static void		cmdl_ctrc(int signal)
{
	if (signal == 2)
		g_loop = 3;
}

static void		canon_mode(int signal)
{
	if (signal == 21)
		g_loop = 6;
}

int				cmdl_signal(char **cmd, char *save, t_win **win)
{
	signal(2, cmdl_ctrc);
	signal(28, cmdl_wins);
	signal(21, canon_mode);
	g_loop == 4 ? winsize(win, &save, cmd) : 0;
	g_loop == 6 ? mode_on(win) : 0;
	g_loop == 6 ? print_prompt(win) : 0;
	if (g_loop == 3)
	{
		if ((*cmd) && (*cmd)[(*win)->cur - (*win)->pr] != 0)
			while ((*cmd)[(*win)->cur - (*win)->pr])
				arrow_rigth(*win, *cmd);
		(*cmd) ? free((*cmd)) : 0;
		save ? free(save) : 0;
		(*win)->hd ? del_hd(&(*win)->hd) : 0;
		(*cmd) = NULL;
		write(1, "\n", 1);
		g_loop = 256;
		return (1);
	}
	g_loop = 256;
	return (0);
}
