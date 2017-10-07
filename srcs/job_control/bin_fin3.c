/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_fin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 02:40:28 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/07 16:38:40 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	addvalue(t_env **env, char *str)
{
	ft_strdel(&(*env)->value);
	if (str)
		(*env)->value = ft_strdup(str);
	else
		(*env)->value = NULL;
}

int		seak(char *s)
{
	char *name;

	if (ft_strcmp(s, "42sh") == 0)
		return (1);
	else if ((name = ft_strrchr(s, '/')))
		if (ft_strcmp(name + 1, "42sh") == 0)
			return (1);
	return (0);
}
