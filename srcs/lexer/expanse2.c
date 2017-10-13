/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:56:57 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/12 23:46:02 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		change_stack(char **str, int j, char *var, char *value)
{
	int		i;
	char	*tmp;

	if (*str + j)
	{
		tmp = ft_strdup(*str + ft_strlen(var) + 1);
		ft_putendl("After var");
		ft_putendl(tmp);
	}
	if (value)
	{
		i = -1;
		ft_bzero(*str + j, ft_strlen(*str + j));
		ft_putendl(*str);
		while (value[++i])
			st_tok(str, value[i], 0);
	}
	if (tmp)
	{
		i = -1;
		while (tmp[++i])
			st_tok(str, tmp[i], 0);
		ft_strdel(&tmp);
	}
	return (0);
}

int		find_stack_loc(char **str, int i, t_local **loc)
{
	char	*new;
	t_local	*tmp;

	if ((tmp = *loc))
		while (tmp)
		{
			if (ft_strstr(*str + (i + 1), tmp->var))
			{
				new = *str + (i + 1 + ft_strlen(tmp->var));
				if (is_space(new[0]) || new[0] == '\0')
					return (change_stack(str, i, tmp->var, tmp->val));
			}
			tmp = tmp->n;
		}
	return (1);
}

int		find_stack_env(char **str, int i, t_env **env)
{
	char	*new;
	t_env	*tmp;

	if ((tmp = *env))
		while (tmp)
		{
			if (ft_strstr(*str + (i + 1), tmp->var))
			{
				new = *str + (i + 1 + ft_strlen(tmp->var));
				if (is_space(new[0]) || new[0] == '\0')
					return (change_stack(str, i, tmp->var, tmp->value));
			}
			tmp = tmp->next;
		}
	return (1);
}

int		stack_expanse(char **str)
{
	int		i;
	char	*new;
	t_local	*loc;
	t_env	*env;

	i = 0;
	loc = *local_slg(0);
	env = (*cmdl_slg())->lstenv;
	if (*str)
		while ((*str)[i])
		{
			if ((*str)[i] == '$' && (*str)[i + 1])
				if (str[i + 1] != '\0' && !is_space((*str)[i + 1]))
					if (find_stack_env(str, i, &env) && find_stack_loc(str, i, &loc))
					{
						new = ft_strndup(*str, i);
						ft_strdel(str);
						*str = ft_strdupf(&new);
					}
			i++;
		}
	return (1);
}
