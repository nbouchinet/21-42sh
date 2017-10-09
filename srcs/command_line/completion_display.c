/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_display.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 16:59:26 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/06 11:39:16 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void 			get_elem_per_line(t_cmdl *cmdl, t_comp **comp,
	size_t winsize, size_t len)
{
	int		col;
	t_comp	*tmp;

	col = 1;
	tmp = *comp;
	while (tmp)
	{
		len += ft_strlen(tmp->str);
		if ((len += ft_strlen(tmp->pad)) < winsize)
			col++;
		else
			break ;
		tmp = tmp->n;
	}
	cmdl->col = col;
}

void 	print_comp(t_comp **comp)
{
	t_comp	*tmp;

	tmp = *comp;
	while (tmp)
	{
		ft_putendl(tmp->str);
		tmp = tmp->n;
	}
}

void 	print_lst(t_comp **comp, t_cmdl *cmdl, size_t *winsize, int *up)
{
	t_comp		*tmp;
	int			len;

	get_elem_per_line(cmdl, comp, *winsize, 0);
	tmp = *comp;
	len = 0;
	while (tmp)
	{
		tmp->bol ? tputs(tgetstr("mr", NULL), 1, ft_putchar) : 0;
		len += ft_printf("%s", tmp->str);
		if ((len + ft_strlen(tmp->pad)) < *winsize)
		{
			len += ft_printf("%s", tmp->pad + 1);
			tputs(tgetstr("me", NULL), 1, ft_putchar);
			write(1, " ", 1);
			!tmp->n ? (*up)++ : 0;
		}
		else
		{
			tmp->n ? ft_printf("%n\n", &len) : 0;
			(*up)++;
		}
		tputs(tgetstr("me", NULL), 1, ft_putchar);
		tmp = tmp->n;
	}
}

int					display_comp(t_cmdl *cmdl, t_comp **comp, int offset)
{
	cmdl->opt |= CCOMP;
	cmdl->offset == -1 ? cmdl->offset = offset : 0;
	if ((*comp) && (*comp)->n)
		call_print_lst(cmdl, comp);
	else if ((*comp))
		call_completion_edit(cmdl, comp, offset);
	else
		write(1, "\7", 1);
	return (1);
}

int					check_comp(t_comp **head, char *name)
{
	t_comp		*tmp;

	tmp = *head;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->str) == 0)
		{
			return (1);
		}
		tmp = tmp->n;
	}
	return (0);
}
