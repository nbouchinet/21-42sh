/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_display2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 16:05:05 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/25 13:06:23 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void 			ft_padd_x(t_comp **comp, int *len, int i)
{
	t_comp		*tmp;
	int			save;

	tmp = *comp;
	*len = 0;
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

static int	comp_len(t_comp **comp)
{
	t_comp		*tmp;
	int			len;

	tmp = *comp;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->n;
	}
	return (len);
}

static int get_nbr_col(t_cmdl *cmdl, t_comp **comp, size_t *winsize)
{
	t_comp	*tmp;
	int		len;
	int		col;

	ft_padd_x(comp, &len, 0);
	*winsize = cmdl->line.co - len - 5;
	tmp = *comp;
	len = 0;
	col = 0;
	while (tmp)
	{
		len += ft_strlen(tmp->str);
		if ((len + ft_strlen(tmp->pad)) < *winsize)
			len += ft_strlen(tmp->pad) + 1;
		else
		{
			tmp->n ? len = 0 : 0;
			col++;
		}
		tmp = tmp->n;
	}
	return (col);
}

void 		call_print_lst(t_cmdl *cmdl, t_comp **comp)
{
	size_t		winsize;
	int			nbr_col;
	int			cur_save;
	int			up;

	up = 0;
	cur_save = cmdl->line.cur;
	while (cmdl->line.str[cmdl->line.cur++ - cmdl->line.pr])
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
	cmdl->line.cur = cur_save;
	write(1, "\n", 1);
	if ((nbr_col = get_nbr_col(cmdl, comp, &winsize)) < cmdl->line.li)
	{
		print_lst(comp, cmdl, &winsize, &up);
		restor_cursor_position(cmdl, up);
	}
	else
	{
		ft_printf("42sh: do ypu want to see all %d possibilities "
		"(y or n) ?", comp_len(comp));
		cmdl->opt |= CCMODE;
	}
}

void 		call_completion_edit(t_cmdl *cmdl, t_comp **comp, int offset)
{
	while ((int)ft_strlen(cmdl->line.str) +
		(int)ft_strlen((*comp)->str + offset) >= cmdl->line.len)
		remalloc_cmdl(&cmdl->line);
	completion_edit(&cmdl->line, comp, NULL, offset);
	!(cmdl->line.cur % cmdl->line.co) ?
	tputs(tgetstr("do", NULL), 1, ft_putchar) : 0;
	comp_del(&cmdl->comp);
	cmdl->opt &= ~(CCOMP);
	cmdl->offset = -1;
}
