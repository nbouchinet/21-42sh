/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:56:57 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/15 13:39:28 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		replace_var(char **str, int *i, int var, char *val)
{
	char	*beg;
	char	*end;

	end = NULL;
	if (*str + (*i) + var + 1)
		end = ft_strdup(*str + (*i) + var + 1);
	if ((*i) != 0)
		beg = ft_strndup(*str, (*i));
	else
		beg = ft_strdup("");
	ft_strdel(str);
	if (val)
	{
		beg = ft_strjoinf(beg, val, 1);
		*i = *i + ft_strlen(val);
	}
	if (end)
		beg = ft_strjoinf(beg, end, 2);
	*str = ft_strdupf(&beg);
	return (0);
}

static int		find_loc(char **str, int *i, t_local **env)
{
	int		var;
	t_local	*tmp;

	if (*env)
	{
		tmp = *env;
		while (tmp)
		{
			var = ft_strlen(tmp->var);
			if (!ft_strncmp(*str + (*i + 1), tmp->var, var))
				return (replace_var(str, i, ft_strlen(tmp->var), tmp->val));
			else
				tmp = tmp->n;
		}
	}
	return (1);
}

static int		find_env(char **str, int *i, t_env **env)
{
	int		var;
	t_env	*tmp;

	if (*env)
	{
		tmp = *env;
		while (tmp)
		{
			var = ft_strlen(tmp->var);
			if (!ft_strncmp(*str + (*i + 1), tmp->var, var))
				return (replace_var(str, i, var, tmp->value));
			else
				tmp = tmp->next;
		}
	}
	return (1);
}

static void		remove_vari(char **str, int i)
{
	int		j;
	char	*beg;
	char	*end;

	j = 0;
	end = NULL;
	while ((*str)[i + j] && !is_space((*str)[i + j]))
		j++;
	if (*str + i + j)
		end = ft_strdup(*str + i + j);
	beg = (i != 0 ? ft_strndup(*str, i) : ft_strdup(""));
	ft_strdel(str);
	end ? beg = ft_strjoinf(beg, end, 3) : 0;
	*str = ft_strdupf(&beg);
}

int				stack_expanse(char **str)
{
	int		i;
	char	*tmp;
	t_local	*loc;
	t_env	*env;

	loc = *local_slg(0);
	env = (*cmdl_slg())->lstenv;
	if (!(*str))
		return (1);
	i = 0;
	tmp = ft_strdup(*str);
	ft_memset(*str, 0, ft_strlen(*str));
	while (tmp[i])
	{
		if (tmp[i] == '$' && tmp[i + 1])
			if (tmp[i + 1] && !is_space(tmp[i + 1]))
				if (find_env(&tmp, &i, &env) && find_loc(&tmp, &i, &loc))
					remove_vari(&tmp, i);
		i++;
	}
	i = -1;
	while (tmp[++i])
		st_tok(str, tmp[i], 0);
	ft_strdel(&tmp);
	return (1);
}
