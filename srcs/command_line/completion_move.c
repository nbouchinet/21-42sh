/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 18:55:00 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 19:05:10 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			c_move(t_comp **comp)
{
	t_comp		*tmp;

	tmp = *comp;
	if (!tmp)
		return (1);
	while (tmp && !tmp->bol)
		tmp = tmp->n;
	tmp->bol = 0;
	if (tmp->n)
		tmp->n->bol = 1;
	else
		(*comp)->bol = 1;
	display_comp(*cmdl_slg(), comp, 0);
	return (1);
}

int			c_arrow_left(t_comp **comp)
{
	t_comp		*tmp;

	tmp = *comp;
	if (!tmp)
		return (1);
	while (tmp && !tmp->bol)
		tmp = tmp->n;
	tmp->bol = 0;
	if (tmp->p)
		tmp->p->bol = 1;
	else
	{
		while (tmp->n)
			tmp = tmp->n;
		tmp->bol = 1;
	}
	display_comp(*cmdl_slg(), comp, 0);
	return (1);
}

int			c_arrow_right(t_comp **comp)
{
	t_comp		*tmp;

	tmp = *comp;
	if (!tmp)
		return (1);
	while (tmp && !tmp->bol)
		tmp = tmp->n;
	tmp->bol = 0;
	if (tmp->n)
		tmp->n->bol = 1;
	else
		(*comp)->bol = 1;
	display_comp(*cmdl_slg(), comp, 0);
	return (1);
}

int			c_arrow_up(t_comp **comp)
{
	t_comp		*tmp;
	int			elem_per_line;

	tmp = *comp;
	elem_per_line = (*cmdl_slg())->col;
	if (!tmp)
		return (1);
	while (tmp && !tmp->bol)
		tmp = tmp->n;
	if (!tmp->p)
		return (c_arrow_left(comp));
	tmp->bol = 0;
	while (tmp->p && elem_per_line--)
		tmp = tmp->p;
	tmp->bol = 1;
	display_comp(*cmdl_slg(), comp, 0);
	return (1);
}

int			c_arrow_down(t_comp **comp)
{
	t_comp		*tmp;
	int			elem_per_line;

	tmp = *comp;
	elem_per_line = (*cmdl_slg())->col;
	if (!tmp)
		return (1);
	while (tmp && !tmp->bol)
		tmp = tmp->n;
	if (!tmp->n)
		return (c_arrow_right(comp));
	tmp->bol = 0;
	while (tmp->n && elem_per_line--)
		tmp = tmp->n;
	tmp->bol = 1;
	display_comp(*cmdl_slg(), comp, 0);
	return (1);
}
