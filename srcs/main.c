/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:01:45 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/11 20:14:18 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void loop(t_cmdl *cmdl)
{
	while (1)
	{
		init_cmdl();
		get_cmdl(cmdl);
		if (cmdl->opt & CCTRLD)
			break ;
		ft_putendl("|");
		ft_printf("\n\n%@%s%@\n\n", BLUE, cmdl->line.str, I);
	}
	unset_shell(cmdl);
}

int         main(int ac, char *av[], char *env[])
{
	t_cmdl          *cmdl;

	ac = 0;
	(void)av;
	cmdl = *cmdl_slg();
	env = check_env(env);
	if (set_shell(cmdl) || get_win_data(cmdl) ||
	    init_env(&cmdl->lstenv, env))
		return (1);
	loop(cmdl);
	return (cmdl->exit ? cmdl->exit : 0);
}
