/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 14:12:58 by zadrien           #+#    #+#             */
//   Updated: 2017/09/04 08:48:50 by nbouchin         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	addvalue(t_env **env, char *str)
{
	ft_strdel(&(*env)->value);
	if (str)
		(*env)->value = ft_strdup(str);
	else
		(*env)->value = ft_strdup("");
}

int		seak(char *s)
{
	char *name;

	if (ft_strcmp(s, "21sh") == 0)
		return (1);
	else if ((name = ft_strrchr(s, '/')))
		if (ft_strcmp(name + 1, "21sh") == 0)
			return (1);
	return (0);
}

char	*var_value(int i, char *var, char *value)
{
	char *str;

	if (!(str = (char*)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	ft_bzero(str, i + 2);
	ft_strcat(str, var);
	ft_strcat(str, "=");
	ft_strcat(str, value);
	return (str);
}

char	**get_env(t_env **lst, char *s)
{
	int		i;
	int		j;
	char	**newenv;
	t_env	*tmp;

	j = 0;
	if ((i = countnode(*lst)) == 0)
		return (NULL);
	if (!(newenv = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	tmp = *lst;
	if (seak(s) == 1)
		increase_shlvl(lst);
	while (tmp)
	{
		i = ft_strlen(tmp->var) + ft_strlen(tmp->value);
		newenv[j] = var_value(i, tmp->var, tmp->value);
		tmp = tmp->next;
		j++;
	}
	newenv[j] = NULL;
	return (newenv);
}
