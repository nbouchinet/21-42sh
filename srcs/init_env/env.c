/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 10:55:26 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/30 19:19:40 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	delete_lstenv(t_env **cmd)
{
	t_env *tmp;

	while ((*cmd))
	{
		tmp = *cmd;
		(*cmd) = (*cmd)->next;
		ft_strdel(&tmp->var);
		ft_strdel(&tmp->value);
		free(tmp);
	}
}

void	print_env(t_env *lst)
{
	while (lst)
	{
		ft_putstr(lst->var);
		ft_putchar('=');
		ft_putstr(lst->value);
		ft_putchar('\n');
		lst = lst->next;
	}
}

void	ft_freetab(char **trash)
{
	int		i;

	i = -1;
	if (!trash)
		return ;
	while (trash[++i])
		ft_strdel(&trash[i]);
	free(trash);
}
