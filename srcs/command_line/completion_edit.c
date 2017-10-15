/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_edit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 18:05:43 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/10 19:01:59 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				only_space_comp(char *str)
{
	while (*str)
		if (*(++str) != ' ')
			return (0);
	write(2, "\033[1mRTFM\033[0m\n", 13);
	print_prompt();
	return (write(2, "\7", 1));
}

void			comp_del(t_comp **head)
{
	t_comp		*tmp;
	t_comp		*save;

	tmp = *head;
	while (tmp)
	{
		save = tmp->n;
		ft_strdel(&tmp->str);
		free(tmp);
		tmp = save;
	}
	*head = NULL;
}

void			check_built_in(t_cmdl *cmdl, char *tmp)
{
	const char	*builtin[5] = {"setenv", "unsetenv", "history", "hash", "env"};
	int			i;

	i = -1;
	while (++i < 5)
		if (ft_strncmp(builtin[i], tmp, ft_strlen(tmp)) == 0)
			fill_comp(&cmdl->comp, (char *)builtin[i], 0, 0);
}

void			completion_edit(t_line *line, t_comp **comp, char *tmp,
			int offset)
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

void			restor_cursor_position(t_cmdl *cmdl, int up)
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
