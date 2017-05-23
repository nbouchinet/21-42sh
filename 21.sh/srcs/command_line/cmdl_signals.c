/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdl_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 11:01:02 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/19 11:01:04 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

extern int g_loop;

void		cmdl_ctrc(int signal)
{
	if (signal == 2)
		g_loop = 3;
}

int		cmdl_signal(char **cmd, char *save, t_win **win)
{
	signal(2, cmdl_ctrc);
	if (g_loop == 3)
	{
		if ((*cmd) && (*cmd)[(*win)->cur - (*win)->pr] != 0)
			while ((*cmd)[(*win)->cur - (*win)->pr])
				arrow_rigth(*win, *cmd);
		(*cmd) ? free((*cmd)) : 0;
		save ? free(save) : 0;
		(*win)->hd ? del_hd((*win)->hd) : 0;
		(*cmd) = NULL;
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}