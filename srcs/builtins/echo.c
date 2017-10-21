/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <hpelat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:35:31 by hpelat            #+#    #+#             */
/*   Updated: 2017/10/15 13:33:32 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				ft_echo(t_ast **ast, t_env **env)
{
	int		i;
	t_ast	*tmp;

	i = 1;
	(void)env;
	(*ast)->right ? io_seq(&(*ast)->right->right, 1) : 0;
	if ((tmp = (*ast)->left->right))
	{
		if (!(i = ft_strcmp(tmp->str, "-n")))
			tmp = tmp->right;
		while (tmp)
		{
			ft_putstr(tmp->str);
			if ((tmp = tmp->right))
				ft_putchar(' ');
		}
	}
	i != 0 ? ft_putchar('\n') : 0;
	return (1);
}
