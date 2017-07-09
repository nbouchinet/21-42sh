/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 10:03:40 by zadrien           #+#    #+#             */
/*   Updated: 2017/07/09 14:43:13 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char		*replace_env(char *str, int s, int len, t_env **env)
{
	char	*beg;
	char	*end;
	char	*var;
	t_env	*var_env;

	beg = ft_strndup(str, s);
	end = ft_strdup(str + (s + len));
	var = ft_strsub(str, s + 1, len - 1);
	if ((var_env = find_node(env, var, NULL)))
		beg = ft_strjoinf(beg, var_env->value, 1);
	beg = ft_strjoinf(beg, end, 1);
	ft_strdel(&end);
	return (beg);
}


static void		check_expanse(char **str, t_env **env)
{
	int		i;
	int		end;
	char	*tmp;

	i = 0;
	while ((*str)[i])
		if ((*str)[i] == '$')
		{
			end = 0;
			while ((*str)[i + end] && is_space((*str)[i + end]) == 0)
				end++;
			if ((tmp = replace_env(*str, i, end, env)))
			{
				ft_strdel(str);
				*str = ft_strdup(tmp);
				ft_strdel(&tmp);
				i = 0;
			}
		}
		else
			i++;
}

static void		tild(char **str, t_env **env)
{
	char 	*tmp;
	char 	*tmp2;
	t_env	*var_env;

	if ((var_env = find_node(env, "HOME", NULL)))
	{
		if ((*str)[0] == '~' && ((*str)[1] == '/' || (*str)[1] == '\0'))
		{
			tmp = ft_strdup((*str) + 1);
			tmp2 = ft_strdup(var_env->value);
			tmp2 = ft_strjoinf(tmp2, tmp, 1);
			ft_strdel(&tmp);
			*str = ft_strdup(tmp2);
			ft_strdel(&tmp2);
		}
	}
}

void			expanse(t_tok **lst, t_env **env)
{
	t_tok	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == DQUOTE || tmp->type == WORD)
		{
			tmp->type == WORD ? tild(&tmp->str, env) : 0;
			check_expanse(&tmp->str, env);
		}
		tmp = tmp->n;
	}
}
