/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_display.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 16:59:26 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/09 16:59:36 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void 	comp_del(t_comp **head)
{
	t_comp 		*tmp;
	t_comp		*save;

	tmp = *head;
	while (tmp)
	{
		save = tmp->n;
		free(tmp->str);
		free(tmp);
		tmp = save;
	}
	tmp = NULL;
}

void 			ft_padd_x(t_comp **comp, int *len, int i)
{
	t_comp		*tmp;
	int			save;

	tmp = *comp;
	while (tmp)
	{
		save = ft_strlen(tmp->str);
		if (save > (*len))
			(*len) = save;
		tmp = tmp->n;
	}
	(*len) += 5;
	tmp = *comp;
	while (tmp)
	{
		i = 0;
		save = ft_strlen(tmp->str);
		ft_memset(tmp->pad, ' ', (*len) - save);
		tmp = tmp->n;
	}
}

static void 	print_lst(t_comp **comp, t_cmdl *cmdl)
{
	t_comp		*tmp;
	size_t		winsize;
	int			len;

	len = 0;
	ft_padd_x(comp, &len, 0);
	tmp = *comp;
	winsize = cmdl->line.co - len - 5;
	len = 0;
	while (tmp)
	{
		len += ft_printf("%s", tmp->str);
		if ((len + ft_strlen(tmp->pad)) < winsize)
			len += ft_printf("%s", tmp->pad);
		else
			tmp->n ? ft_printf("%n\n", &len) : 0;
		tmp = tmp->n;
	}
	write(1, "\n", 1);
	if (cmdl->line.pr == 3)
		print_prompt();
	else if (cmdl->opt & SQ || cmdl->opt & DQ)
		write(1, cmdl->opt & SQ ? "quote> " : "dquote> ",
		cmdl->opt & SQ ? 7 : 8);
	write(1, cmdl->line.str, ft_strlen(cmdl->line.str));
}

int 			display_comp(t_cmdl *cmdl, t_comp **comp, int offset)
{
	int			pos;

	if (!(*comp)->n && (int)ft_strlen(cmdl->line.str) + offset >= cmdl->line.len)
		remalloc_cmdl(&cmdl->line, ft_strlen(cmdl->line.str));
	if ((*comp) && (*comp)->n)
	{
		pos = cmdl->line.cur;
		end(cmdl);
		write(1, "\n", 1);
		print_lst(comp, cmdl);
		!(cmdl->line.cur % cmdl->line.co) ?
		tputs(tgetstr("do", NULL), 1, ft_putchar) : 0;
		while (cmdl->line.cur > pos)
			arrow_left(cmdl);
	}
	else if ((*comp))
	{
		completion_edit(&cmdl->line, comp, NULL, offset);
		!(cmdl->line.cur % cmdl->line.co) ?
		tputs(tgetstr("do", NULL), 1, ft_putchar) : 0;
	}
	else
		beep();
	comp ? comp_del(comp) : 0;
	return (!comp ? 0 : 1);
}

int				check_comp(t_comp **head, char *name)
{
	t_comp 		*tmp;

	tmp = *head;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->str))
			return (1);
		tmp = tmp->n;
	}
	return (0);
}
