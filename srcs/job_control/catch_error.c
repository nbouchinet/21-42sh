/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:33:40 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/19 13:39:06 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		catch_error(t_job **job, int status)
{
	(*job)->notified = 1;
	if (status == SIGSEGV)
		fd_printf(2, "Segmentation fault: 11\n");
	else if (status == SIGABRT)
		fd_printf(2, "Abort trap: 6\n");
	else if (status == SIGBUS)
		fd_printf(2, "Bus error: 10\n");
	else if (status == SIGTSTP)
		fd_printf(2, "[%d]+  Stopped	%s\n", (*job)->num, (*job)->command);
}
