/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 10:03:40 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/11 20:19:50 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

t_local			*find_local(t_local **local, char *var)
{
	t_local		*tmp;

	if (*local)
	{
		tmp = *local;
		while (tmp && ft_strcmp(var, tmp->var) != 0)
			tmp = tmp->n;
		return (tmp);
	}
	return (NULL);
}

static char		*replace_env(char *str, int s, int len, t_env **env)
{
	char	*beg;
	char	*end;
	char	*var;
	t_local	*tmp;
	t_env	*var_env;

	ft_putendl("=========");
	beg = ft_strndup(str, s);
	ft_putendl(beg);
	end = ft_strdup(str + (s + len));
	ft_putendl(end);
	var = ft_strsub(str, s + 1, len - 1);
	ft_putendl(var);
	ft_putendl("=========");
	if (var && (var_env = find_node(env, var, NULL)))
		beg = ft_strjoinf(beg, var_env->value, 1);
	else if ((tmp = find_local(local_slg(0), var)))
		beg = ft_strjoinf(beg, tmp->val, 1);
	else
	{
		ft_strdel(&beg);
		ft_strdel(&end);
		ft_strdel(&var);
		return (NULL);
	}
	beg = ft_strjoinf(beg, end, 3);
	free(var);
	return (beg);
} // a refaire

static int		check_expanse(char **str, t_env **env, int i)
{
	int		end;
	char	*tmp;

	while ((*str)[i])
		if ((*str)[i] == '$')
		{
			end = 0;
			while ((*str)[i + end] && !is_space((*str)[i + end]))
				end++;
			if (!ft_strcmp("$", *str))
				return (0);
			if ((tmp = replace_env(*str, i, end, env)))
			{
				ft_strdel(str);
				(*str = ft_strdup(tmp)) ? ft_strdel(&tmp) : 0;
				i = 0;
			}
			else
				return (1);
		}
		else
			i++;
	return (0);
}

static void		tild(char **str, t_env **env)
{
	char	*tmp;
	char	*tmp2;
	t_env	*var_env;

	if ((*str) && (*str)[0] == '~' && ((*str)[1] == '/' || (*str)[1] == '\0'))
		if ((var_env = find_node(env, "HOME", NULL)) && var_env->value)
		{
			tmp = ft_strdup((*str) + 1);
			ft_strdel(str);
			tmp2 = ft_strdup(var_env->value);
			tmp2 = ft_strjoinf(tmp2, tmp, 3);
			*str = ft_strdupf(&tmp2);
		}
}

void			expanse(t_tok **lst, t_env **env)
{
	t_tok	*tmp;
	t_tok	*prev;
	t_tok	*save;

	tmp = *lst;
	prev = NULL;
	save = NULL;
	while (tmp)
	{
		if (tmp->type == DQUOTE || tmp->type == WORD)
		{
			tmp->type == WORD ? tild(&tmp->str, env) : 0;
			if (check_expanse(&tmp->str, env, 0))
			{
				save = tmp;
				!prev ? *lst = tmp->n : 0;
				prev ? prev->n = tmp->n : 0;
			}
		}
		prev = tmp;
		tmp = tmp->n;
		save ? ft_strdel(&save->str) : 0;
		save ? free(save) : 0;
		save ? save = NULL : 0;
	}
}
