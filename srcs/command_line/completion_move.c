/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 18:55:00 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/17 18:55:15 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void 	comp_del(t_comp **head)
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

int		c_arrow_left(t_comp **comp)
{
	t_comp	*tmp;

	tmp = *comp;
	if (!tmp)
		return (1);
	while (!tmp->bol)
		tmp = tmp->n;
	tmp->bol = 0;
	if (tmp->p)
		tmp->p->bol = 1
	else
		while (tmp->n)
			tmp = tmp->n;
	tmp->bol = 1;
}

int		c_arrow_right(t_comp **comp)
{
	t_comp	*tmp;

	tmp = *comp;
	if (!tmp)
		return (1);
	while (!tmp->bol)
		tmp = tmp->n;
	tmp->bol = 0;
	tmp->n ? tmp->n->bol = 1 : (*comp)->bol = 1;
	return (1);
}

int		c_arrow_up(t_comp **comp)
{
	t_comp	*tmp;
	int		c_size;

	tmp = *comp;
	c_size = (*comp)->col;
	if (!tmp)
		return (1);
	if (!tmp->p)
		return (c_arrow_left(comp));
	tmp->bol = 0;
	while (tmp->n && c_size--)
		tmp = tmp->n;
	tmp->bol = 1;
}

int		c_arrow_down(t_comp **comp)
{
	t_comp	*tmp;
	int		c_size;

	tmp = *comp;
	c_size = (*comp)->col;
	if (!tmp)
		return (1);
	if (!tmp->n)
		return (c_arrow_right(comp));
	tmp->bol = 0;
	while (tmp->n && c_size--)
		tmp = tmp->n;
	tmp->bol = 1;
}
