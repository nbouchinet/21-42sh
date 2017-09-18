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

static void 			get_nbr_col(t_cmdl *cmdl, t_comp **comp, size_t winsize,
	size_t len)
{
	int		col;
	t_comp	*tmp;

	col = 1;
	tmp = *comp;
	while (tmp)
	{
		len += ft_strlen(tmp->str);
		if ((len = len + ft_strlen(tmp->pad)) < winsize)
			col++;
		else
			break ;
		tmp = tmp->n;
	}
	cmdl->col = col;
}

static void 			ft_padd_x(t_comp **comp, int *len, int i)
{
	t_comp		*tmp;
	int			save;

	tmp = *comp;
	while (tmp)
	{
		save = ft_strlen(tmp->str);
		if (save > *len)
			*len = save;
		tmp = tmp->n;
	}
	*len += 5;
	tmp = *comp;
	while (tmp)
	{
		i = 0;
		save = ft_strlen(tmp->str);
		ft_memset(tmp->pad, ' ', *len - save);
		tmp = tmp->n;
	}
}

void 	print_lst(t_comp **comp, t_cmdl *cmdl, int len, int up)
{
	t_comp		*tmp;
	size_t		winsize;

	ft_padd_x(comp, &len, 0);
	tmp = *comp;
	winsize = cmdl->line.co - len - 5;
	get_nbr_col(cmdl, comp, winsize, 0);
	len = 0;
	while (tmp)
	{
		tmp->bol ? tputs(tgetstr("mr", NULL), 1, ft_putchar) : 0;
		len += ft_printf("%s", tmp->str);
		if ((len + ft_strlen(tmp->pad)) < winsize)
		{
			len += ft_printf("%s", tmp->pad + 1);
			tputs(tgetstr("me", NULL), 1, ft_putchar);
			write(1, " ", 1);
			!tmp->n ? up++ : 0;
		}
		else
		{
			tmp->n ? ft_printf("%n\n", &len) : 0;
			up++;
		}
		tputs(tgetstr("me", NULL), 1, ft_putchar);
		tmp = tmp->n;
	}
	restor_cursor_position(cmdl, up);
}

int 			display_comp(t_cmdl *cmdl, t_comp **comp, int offset)
{
	int			pos;
	int			cur_save;

	cmdl->opt |= CCOMP;
	cmdl->offset == -1 ? cmdl->offset = offset : 0;
	if ((*comp) && !(*comp)->n && (int)ft_strlen(cmdl->line.str) + offset >=
	cmdl->line.len)
		remalloc_cmdl(&cmdl->line, ft_strlen(cmdl->line.str));
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	if ((*comp) && (*comp)->n)
	{
		pos = cmdl->line.cur;
		cur_save = cmdl->line.cur;
		end(cmdl);
		cmdl->line.cur = cur_save;
		write(1, "\n", 1);
		print_lst(comp, cmdl, 0, 0);
	}
	else if ((*comp))
	{
		completion_edit(&cmdl->line, comp, NULL, offset);
		!(cmdl->line.cur % cmdl->line.co) ?
		tputs(tgetstr("do", NULL), 1, ft_putchar) : 0;
		comp_del(&cmdl->comp);
		cmdl->opt &= ~(CCOMP);
		cmdl->offset = -1;
	}
	else
		beep();
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
