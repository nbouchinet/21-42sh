/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:48:33 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/10 16:48:59 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		ctrl_l(t_win **win, char **cmd)
{
    char    buf[3];

	ft_putendl("hello");
	buf[0] = 27;
	buf[1] = 91;
	buf[2] = 68;
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	if ((*win)->sh)
		exit_sh_mode(*win, &(*win)->his, cmd, buf);
	else
	{
		tputs(tgetstr("cl", NULL), 1, ft_putchar);
		print_prompt(win);
		write(1, (*cmd), ft_strlen(*cmd));
	}
}
