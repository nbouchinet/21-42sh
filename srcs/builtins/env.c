/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 08:33:23 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/24 13:56:49 by zadrien          ###   ########.fr       */
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

int		init_env(t_env **lst, char **env)
{
	int		i;
	char	**envtab;
	t_env	*tmp;

	i = -1;
	env && !env[0] ? *lst = NULL : 0;
	if (env && env[0])
		if (!(*lst = (t_env*)malloc(sizeof(t_env))))
			return (fd_printf(2, "malloc error\n"));
	tmp = *lst;
	while (env[++i])
	{
		envtab = ft_strsplit(env[i], '=');
		tmp->var = ft_strdup(envtab[0]);
		tmp->value = ft_strdup(envtab[1]);
		if (env[i + 1])
		{
			if (!(tmp->next = (t_env*)malloc(sizeof(t_env))))
				return (fd_printf(2, "malloc error\n"));
			tmp = tmp->next;
		}
		ft_freetab(envtab);
	}
	tmp ? tmp->next = NULL : 0;
	return (0);
}
