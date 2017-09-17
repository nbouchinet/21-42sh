/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_edit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 18:05:43 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/10 18:05:45 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void 	completion_edit(t_line *line, t_comp **comp, char *tmp, int offset)
{
	tmp = line->str[line->cur - line->pr] ?
	ft_strdup(line->str + (line->cur - line->pr)) : NULL;
	if (!tmp)
	{
		line->str = ft_strcat(line->str, (*comp)->str + offset);
		write(1, line->str + (line->cur - line->pr),
		ft_strlen(line->str + (line->cur - line->pr)));
		line->cur = ft_strlen(line->str) + line->pr;
	}
	else
	{
		ft_memset(line->str + (line->cur - line->pr), 0,
		ft_strlen(line->str + (line->cur - line->pr)));
		line->str = ft_strcat(line->str, (*comp)->str + offset);
		write(1, line->str + (line->cur - line->pr),
		ft_strlen(line->str + (line->cur - line->pr)));
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		line->cur = ft_strlen(line->str) + line->pr;
		line->str = ft_strcat(line->str, tmp);
		write(1, line->str + (line->cur - line->pr),
		ft_strlen(line->str + (line->cur - line->pr)));
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
		tmp ? free(tmp) : 0;
	}
}

void 	restor_cursor_position(t_cmdl *cmdl, int up)
{
	int		save;

	save = cmdl->line.cur;
	while (up--)
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
	cmdl->line.cur = 0;
	while (cmdl->line.cur < save)
	{
		cmdl->line.cur += 1;
		if (cmdl->line.cur % cmdl->line.co == 0)
			tputs(tgetstr("do", NULL), 1, ft_putchar);
		else
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
	}
}
