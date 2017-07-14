/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ccp_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 16:14:30 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/13 16:14:39 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void 	get_be(t_win *win, char buf[])
{
	static int which = 0;

	if (CUT)
	{
		if (which == 2)
		{
			win->cpy_b = -1;
			win->cpy_e = -1;
		}
		which = 1;
		win->cpy_b != -1 && win->cpy_e == -1 ? win->cpy_e = win->cur - win->pr : 0;
		win->cpy_b == -1 && win->cpy_e == -1 ? win->cpy_b = win->cur - win->pr : 0;
	}
	else
	{
		if (which == 1)
		{
			win->cpy_b = -1;
			win->cpy_e = -1;
		}
		which = 2;
		win->cpy_b != -1 && win->cpy_e == -1 ? win->cpy_e = win->cur - win->pr : 0;
		win->cpy_b == -1 && win->cpy_e == -1 ? win->cpy_b = win->cur - win->pr : 0;
	}
}
