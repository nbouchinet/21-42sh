/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:35:31 by hpelat            #+#    #+#             */
/*   Updated: 2017/06/06 16:14:27 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				ft_echo(t_ast **ast, t_env **env)
{
	int		i;
	char	**arg;

	(void)env;
	if (!(arg = creat_arg_env(&(*ast)->left->right)) || !arg[0])
		return (write(1, "\n", 1));
	i = (arg[0] && !ft_strcmp(arg[0], "-n") ? 1 : 0);
	while (arg[i])
	{
		if (write(1, arg[i], ft_strlen(arg[i])) && arg[++i])
			write(1, " ", 1);
	}
	if (arg && arg[0] && !ft_strcmp(arg[0], "-n"))
	{
		if (arg[1])
		{
			tputs(tgetstr("mr", NULL), 1, ft_putchar);
			write(1, "%\n", 2);
			tputs(tgetstr("me", NULL), 1, ft_putchar);
		}
	}
	else
		ft_putendl("");
	ft_free(arg, NULL, 1);
	return (1);
}
