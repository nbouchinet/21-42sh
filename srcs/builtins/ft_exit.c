/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:11:48 by hpelat            #+#    #+#             */
/*   Updated: 2017/06/09 16:11:51 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int	g_loop;

int		ft_exit(t_ast **ast, t_env **env)
{
	int		i;
	char	**arg;

	(void)env;
	if (!(arg = creat_arg_env(&(*ast)->left->right)))
		return ((g_loop = 0) ? 1 : 1);
	i = (arg[0][0] == '-' && arg[0][1] ? 0 : -1);
	while (arg[0][++i])
		if (!ft_isdigit(arg[0][i]))
		{
			fd_printf(2, "42sh: exit: %@: numeric argument required\n", arg[0]);
			ft_free(arg, NULL);
			return (((g_loop = 255) > 0 ? 0 : 0));
		}
	if (arg[1] && fd_printf(2, "42sh: exit: too many arguments\n"))
	{
		ft_free(arg, NULL);
		return (((g_loop = 256) > 0 ? 0 : 0));
	}
	g_loop = ft_atoi(arg[0]);
	while (g_loop > 255 || g_loop < 0)
		g_loop = (g_loop > 255 ? g_loop - 256 : g_loop + 256);
	ft_free(arg, NULL);
	return (1);
}
