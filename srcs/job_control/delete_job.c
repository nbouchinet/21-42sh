/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 21:45:46 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 14:43:35 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		delete_job(t_job **job)
{
	t_job		*j;
	t_process	*p;
	t_process	*tmp;

	j = *job;
	if (j)
	{
		if (j->command)
			ft_strdel(&j->command);
		p = j->first_process;
		while (p)
		{
			tmp = p;
			if (tmp->argv)
				ft_freetab(tmp->argv);
			if (tmp->rdir)
				tmp->rdir = NULL;
			if (tmp->builtin)
				tmp->builtin = NULL;
			p = p->next;
			free(tmp);
		}
		free(j);
	}
	return (0);
}
