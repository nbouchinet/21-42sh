/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 14:08:34 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/03 14:08:45 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	check(t_env **env, char **arg)
{
	int		len;

	len = ft_tab_len(arg);
	if (len == 2)
		return (fd_printf(2, "cd: string not in pwd: %s\n", arg[0]));
	else if (len > 2)
		return (fd_printf(2, "cd: too many arguments\n");
	if (arg[0][0] == '~' && !(*env))
		return (fd_printf(2, "cd: HOME not set\n"));
	else if (arg[0][0] == '-' && arg[0][0] == 0 && !(*env))
		return (fd_printf(2, "cd: OLDPWD not set\n"));
	if ((*env))
	{

	}
}

int     	cd(t_ast **ast, t_env **env)
{
	char	**arg;
	int		opt;

	arg = creat_arg_env(&(*ast)->rigth);
	if (!check(env, arg))
		return ;
}