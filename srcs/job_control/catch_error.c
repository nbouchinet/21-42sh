/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:33:40 by nbouchin          #+#    #+#             */
/*   Updated: 2017/09/14 18:14:37 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		catch_error(t_job **job, int status)
{
	(*job)->notified = 1;
	if (WTERMSIG(status) == SIGSEGV)
		fd_printf(2, "Segmentation fault: 11\n");
	else if (WTERMSIG(status) == SIGABRT)
		fd_printf(2, "Abort trap: 6\n");
	else if (WTERMSIG(status) == SIGBUS)
		fd_printf(2, "Bus error: 10\n");
	else if (WSTOPSIG(status) == SIGTSTP)
		fd_printf(2, "[%d]+  Stopped	%s\n", (*job)->num, (*job)->command);
}
