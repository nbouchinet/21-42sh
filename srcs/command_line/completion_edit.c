/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_edit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 18:05:43 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/06 11:46:47 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_comp  *fill_builtin(t_comp **comp, char *builin)
{
	t_comp	*tmp;
	t_comp	*stock;
	int		i;

	i = 0;
	if (!(tmp = (t_comp *)malloc(sizeof(t_comp))))
		exit(EXIT_FAILURE);
	tmp->str = ft_strdup(builin);
	ft_memset(tmp->pad, 0, 512);
	tmp->bol = 0;
	tmp->n = NULL;
	tmp->p = NULL;
	if (!(*comp))
		return (tmp);
	stock = *comp;
	while (stock && ft_strcmp(stock->str, builin) < 0)
	{
		i++;
		stock = stock->n;
	}
	insert(comp, tmp, i);
	return (tmp);
}

void 	check_built_in(t_cmdl *cmdl, char *tmp)
{
	char	*builtin[5] = {"setenv", "unsetenv", "history", "hash", "env"};
	int		i;

	i = -1;
	while (++i < 5)
	{
		if (ft_strncmp(builtin[i], tmp, ft_strlen(tmp)) == 0)
			!cmdl->comp ? cmdl->comp = fill_builtin(&cmdl->comp, builtin[i]) :
			fill_builtin(&cmdl->comp, builtin[i]);
	}
}

void 	completion_edit(t_line *line, t_comp **comp, char *tmp, int offset)
{
	if (!(tmp = ft_strdup(line->str + (line->cur - line->pr))))
	{
		line->str = ft_strcat(line->str, (*comp)->str + offset);
		write(1, line->str + (line->cur - line->pr),
		ft_strlen(line->str + (line->cur - line->pr)));
		line->cur = ft_strlen(line->str) + line->pr;
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
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
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
		ft_strdel(&tmp);
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
