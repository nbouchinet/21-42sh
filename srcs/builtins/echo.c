/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <hpelat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:35:31 by hpelat            #+#    #+#             */
/*   Updated: 2017/10/11 14:42:38 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				ft_echo(t_ast **ast, t_env **env)
{
	int		i;
	char	**arg;

	(void)env;
	(*ast)->right ? io_seq(&(*ast)->right->right, 1) : 0;
	if (!(arg = creat_arg_env(&(*ast)->left->right)) || !arg[0])
		return (write(1, "\n", 1));
	i = (arg[0] && !ft_strcmp(arg[0], "-n") ? 1 : 0);
	while (arg[i])
	{
		ft_putstr(arg[i]);
		if (arg[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (ft_strcmp(arg[0], "-n"))
		ft_putchar('\n');
	ft_free(arg, NULL, 1);
	return (1);
}
