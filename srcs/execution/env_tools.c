/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 17:37:46 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/30 18:54:16 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		countnode(t_env *env)
{
	int		i;

	i = 0;
	if (!env)
		return (i);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	increase_shlvl(t_env **env)
{
	int		i;
	t_env	*tmp;
	char	*c;

	if (!(tmp = find_node(env, "SHLVL", NULL)))
		return ;
	i = ft_atoi(tmp->value) + 1;
	c = ft_itoa(i);
	addvalue(&tmp, c);
	free(c);
}

void	reduc_shlvl(t_env **env, char *s)
{
	int		i;
	t_env	*tmp;
	char	*c;

	if (seak(s) == 0)
		return ;
	if (!(tmp = find_node(env, "SHLVL", NULL)))
		return ;
	i = ft_atoi(tmp->value);
	i--;
	c = ft_itoa(i);
	addvalue(&tmp, c);
	free(c);
}
