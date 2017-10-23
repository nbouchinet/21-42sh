/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 15:06:31 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/19 13:39:23 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	job_len(t_job **j, t_job **table, int *len)
{
	(*j) = *table;
	while (*j)
	{
		(*j) = (*j)->next;
		(*len)++;
	}
	(*j) = *table;
}

void	print_job_message(t_job **j, int *len, int *pos)
{
	int	symb;

	symb = ' ';
	while ((*j))
	{
		(*pos)++;
		((*len) == (*pos)) ? symb = '+' : 0;
		((*len) - 1 == (*pos)) ? symb = '-' : 0;
		if ((*j)->status == SIGSEGV)
			fd_printf(2, "[%d]%c %d Segmentation fault: 11 \t%s\n",
			(*j)->num, symb, (*j)->pgid, (*j)->command);
		else if ((*j)->status == SIGABRT)
			fd_printf(2, "[%d]%c %d Abort trap: 6 \t\t%s\n",
			(*j)->num, symb, (*j)->pgid, (*j)->command);
		else if ((*j)->status == SIGTSTP)
			fd_printf(2, "[%d]%c %d Bus error: 10 \t\t%s\n",
			(*j)->num, symb, (*j)->pgid, (*j)->command);
		else if ((*j)->status == 15)
			fd_printf(2, "[%d]%c %d Terminated: \t\t15 %s\n",
			(*j)->num, symb, (*j)->pgid, (*j)->command);
		else
			fd_printf(2, "[%d]%c %d Stopped\t\t\t%s\n",
			(*j)->num, symb, (*j)->pgid, (*j)->command);
		(*j) = (*j)->next;
	}
}
