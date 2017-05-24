/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 13:47:15 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/24 13:47:18 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int  g_loop;

void        winsize(t_win **win, char **save, char **cmd)
{
	char    *line;

	line = (*save) ? (*save) : (*cmd);
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	get_win_data(win);
	print_prompt();
	write(1, line, ft_strlen(line));
	g_loop = 1;
}