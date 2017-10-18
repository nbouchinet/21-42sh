/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:41:42 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/18 16:09:41 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		insert_str(t_line *line, char *str, int i, int j)
{
	char	*tmp;

	tmp = ft_strdup(line->str + (line->cur - line->pr));
	while (str[++i])
	{
		if (str[i] == '\n')
			break ;
		line->str[line->cur++ - line->pr] = str[i];
	}
	i = line->cur - line->pr;
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	while (tmp[++j])
		line->str[line->cur++ - line->pr] = tmp[j];
	write(1, line->str + i, ft_strlen(line->str + i));
	line->cur -= (line->cur - line->pr) - i;
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	if (tmp)
		ft_strdel(&tmp);
}

static void		end_print(t_line *line, char *str, int len_cpy)
{
	while ((int)ft_strlen(line->str) + len_cpy >= line->len)
		remalloc_cmdl(line);
	if (line->str[line->cur - line->pr] == 0)
	{
		line->str = ft_strcat(line->str, str);
		line->cur += len_cpy;
	}
	else
		insert_str(line, str, -1, -1);
}

int				graphical_print(t_cmdl *cmdl, char buf[])
{
	char	*save;

	save = buf;
	while (*buf)
	{
		if (*buf == '\n')
			*buf = ' ';
		buf++;
	}
	write(1, save, ft_strlen(save));
	end_print(&cmdl->line, save, ft_strlen(save));
	return (1);
}
