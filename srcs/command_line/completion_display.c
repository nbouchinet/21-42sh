/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_display.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 16:59:26 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/11 20:05:45 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void 	get_nbr_col(t_comp **comp, int len)
{
	t_comp		*tmp;
	int			col;

	tmp = *comp;
	col = 0;
	while ((len + ft_strlen(tmp->pad)) < winsize)
	{
		col++;
		len += ft_printf("%s", tmp->str);
		tmp = tmp->n;
	}
	(*comp)->col = col;
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

static void 	print_lst(t_comp **comp, t_cmdl *cmdl, int len, int up)
{
	t_comp		*tmp;
	size_t		winsize;

	ft_padd_x(comp, &len, 0);
	get_nbr_col(comp, len);
	tmp = *comp;
	winsize = cmdl->line.co - len - 5;
	tmp->bol = 1;
	while (tmp)
	{
		tmp->bol ? tputs(tgetstr("mr", NULL), 1, ft_putchar) : 0;
		len += ft_printf("%s", tmp->str);
		if ((len + ft_strlen(tmp->pad)) < winsize)
		{
			len += ft_printf("%s", tmp->pad + 1);
			tputs(tgetstr("me", NULL), 1, ft_putchar);
			write(1, " ", 1);
		}
		else if ((up++))
			tmp->n ? ft_printf("%n\n", &len) : 0;
		tputs(tgetstr("me", NULL), 1, ft_putchar);
		tmp = tmp->n;
	}
	restor_cursor_position(cmdl, up);
}

int 			display_comp(t_cmdl *cmdl, t_comp **comp, int offset)
{
	int			pos;

	if (!(*comp)->n && (int)ft_strlen(cmdl->line.str) + offset >= cmdl->line.len)
		remalloc_cmdl(&cmdl->line, ft_strlen(cmdl->line.str));
	if ((*comp) && (*comp)->n)
	{
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		pos = cmdl->line.cur;
		end(cmdl);
		write(1, "\n", 1);
		print_lst(comp, cmdl, 0, 0);
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
