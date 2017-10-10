/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 15:06:31 by nbouchin          #+#    #+#             */
/*   Updated: 2017/10/10 15:06:43 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_job(t_job **job, t_ast **ast, t_job **table)
{
	t_job		*j;
	t_job		*prev;

	(void)job;
	(void)ast;
	if ((j = *table))
	{
		prev = NULL;
		while (j)
			if (!check_j(table, &j, &prev))
				break ;
	}
	return (1);
}

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
			fd_printf(2, "[%d]%c Segmentation fault: 11 \t%s\n",
			(*j)->num, symb, (*j)->command);
		else if ((*j)->status == SIGABRT)
			fd_printf(2, "[%d]%c Abort trap: 6 \t\t%s\n",
			(*j)->num, symb, (*j)->command);
		else if ((*j)->status == SIGTSTP)
			fd_printf(2, "[%d]%c Bus error: 10 \t\t%s\n",
			(*j)->num, symb, (*j)->command);
		else if ((*j)->status == 15)
			fd_printf(2, "[%d]%c Terminated: \t\t15 %s\n",
			(*j)->num, symb, (*j)->command);
		else
			fd_printf(2, "[%d]%c Stopped\t\t\t%s\n",
			(*j)->num, symb, (*j)->command);
		(*j) = (*j)->next;
	}
}
