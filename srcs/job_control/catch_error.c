//****************************************************************************//
//                                                                            //
//                                                        :::      ::::::::   //
//   catch_error.c                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/08/29 09:56:12 by nbouchin          #+#    #+#             //
//   Updated: 2017/08/29 10:18:20 by nbouchin         ###   ########.fr       //
//                                                                            //
//****************************************************************************//

#include "header.h"

void		catch_error(t_process **process)
{
	if (WIFSIGNALED((*process)->status))
	{
		ft_putendl("SALUT JE SUIS LA");
		if (WSTOPSIG((*process)->status) == SIGSEGV)
		{
			fd_printf(2, "[1]	%d segmentation fault %s\n", (*process)->pid, (*process)->argv[0]);	
		}
		else if (WSTOPSIG((*process)->status) == SIGABRT)
		{
			fd_printf(2, "[1]	%d segmentation fault %s\n", (*process)->pid, (*process)->argv[0]);
		}
		else if (WSTOPSIG((*process)->status) == SIGBUS)
		{
			fd_printf(2, "[1]	%d segmentation fault %s\n", (*process)->pid, (*process)->argv[0]);	
		}
	}
}
