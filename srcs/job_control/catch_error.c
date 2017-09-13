/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:33:40 by nbouchin          #+#    #+#             */
/*   Updated: 2017/09/13 11:33:41 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		catch_error(t_job **job, int status)
{
	if (WTERMSIG(status) == SIGSEGV)
		fd_printf(3, "Segmentation fault: 11\n");
	else if (WTERMSIG(status) == SIGABRT)
		fd_printf(3, "Abort trap: 6\n");
	else if (WTERMSIG(status) == SIGBUS)
		fd_printf(3, "Bus error: 10\n");
	else if (WSTOPSIG(status) == SIGTSTP)
		fd_printf(3, "[%d]+  Stopped	%s\n", 1, (*job)->command);
}
