/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_all.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 12:56:49 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/09 12:56:58 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void 	del_all(t_cmdl **cmdl_head, t_his **his_head)
{
	t_cmdl		*cmdl;
	t_his		*his;
	t_his		*save;

	cmdl = *cmdl_head;
	his = *his_head;
	cmdl->line.str ? ft_strdel(&cmdl->line.str) : 0;
	cmdl->line.save ? ft_strdel(&cmdl->line.save) : 0;
	cmdl->ccp.cpy ? ft_strdel(&cmdl->ccp.cpy) : 0;
	while (his)
	{
		save = his->n;
		ft_strcmp(his->cmdl, "") ? free(his->cmdl) : 0;
		free(his);
		his = save;
	}
	his = NULL;
}
