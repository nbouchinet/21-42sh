/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_edit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 18:05:43 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/13 09:38:24 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	completion_edit(t_line *line, t_comp **comp, char *tmp, int offset)
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
	int		nd;

	save = cmdl->line.cur - cmdl->line.pr;
	nd = cmdl->line.pr;
	while (up)
	{
		up--;
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	}
	tputs(tgetstr("cr", NULL), 1, ft_putchar);
	while (nd)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		nd--;
	}
	cmdl->line.cur = cmdl->line.pr;
	while ((cmdl->line.cur - cmdl->line.pr) < save)
	{
		cmdl->line.cur += 1;
		if (cmdl->line.cur % cmdl->line.co == 0)
			tputs(tgetstr("do", NULL), 1, ft_putchar);
		else
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
	}
}
