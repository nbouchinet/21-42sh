/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <hpelat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:11:48 by hpelat            #+#    #+#             */
/*   Updated: 2017/10/10 19:43:13 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		set_exiting_value(t_cmdl **cmdl, int r_value)
{
	if ((*cmdl)->ret != 0 && (*cmdl)->ret != 256)
		(*cmdl)->ret += 128;
	else if ((*cmdl)->ret == 256)
		(*cmdl)->ret -= 255;
	(*cmdl)->exit = (*cmdl)->ret;
	return (r_value);
}

int		ft_exit(t_ast **ast, t_env **env)
{
	int		i;
	char	**arg;
	t_cmdl	**cmdl;

	(void)env;
	(*ast)->right ? io_seq(&(*ast)->right->right) : 0;
	cmdl = cmdl_slg();
	if (!(arg = creat_arg_env(&(*ast)->left->right)))
		return (set_exiting_value(cmdl, 1));
	i = (arg[0][0] == '-' && arg[0][1] ? 0 : -1);
	while (arg[0][++i])
		if (!ft_isdigit(arg[0][i]))
		{
			fd_printf(2, "42sh: exit: %@: numeric argument required\n", arg[0]);
			ft_free(arg, NULL, 1);
			return ((((*cmdl)->exit = 255) > 0 ? 0 : 0));
		}
	if (arg[1] && fd_printf(2, "42sh: exit: too many arguments\n") &&
	ft_free(arg, NULL, 1))
		return ((((*cmdl)->exit = 256) > 0 ? 0 : 0));
	(*cmdl)->exit = ft_atoi(arg[0]);
	while ((*cmdl)->exit > 255 || (*cmdl)->exit < 0)
		(*cmdl)->exit = ((*cmdl)->exit > 255 ? (*cmdl)->exit - 256 :
		(*cmdl)->exit + 256);
	return (ft_free(arg, NULL, 1));
}
