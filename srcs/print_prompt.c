/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 14:57:54 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/24 13:46:07 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int		g_loop;

void		print_prompt(t_win **win)
{
	char	buff[1024];

	if ((*win)->lstenv)
		ft_printf("%@42sh: %s%@", H_YELLOW, lst_at(&(*win)->lstenv, "PWD")->value, I);
	else
	{
		getcwd(buff, 1024);
		ft_printf("%@42sh: %s\n%", H_YELLOW, buff, I);
	}
	if ((!(*win)->quote && !(*win)->hd))
		write(1, "\n$> ", 4);
	else if ((*win)->quote)
		(*win)->quote == 1 ? write(1, "\nquote> ", 8) : write(1, "\ndquote> ", 9);
	else if ((*win)->hd)
		write(1, "heredoc> ", 9);
	g_loop = 256;
}
