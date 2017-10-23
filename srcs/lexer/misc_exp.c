/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:56:57 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/18 11:54:21 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void			tild(t_tok **lst, char **stack, char *line, int *i)
{
	int		j;
	t_env	*env;

	j = -1;
	(void)lst;
	if (is_space(line[(*i) + 1]) || !line[(*i) + 1] || line[(*i) + 1] == '/')
		if ((env = find_node(&(*cmdl_slg())->lstenv, "HOME", NULL)) &&
			env->value)
		{
			while (env->value[++j])
				st_tok(stack, env->value[j], 0);
			return ;
		}
	st_tok(stack, line[(*i)], 0);
}

void			lexer_exp(t_tok **lst, char **stack, char *line, int *i)
{
	(void)lst;
	expanse_stack(stack, line, i);
	(*i)--;
}

void			complete_st_quote(char **stack, char **ins, char **str)
{
	int		i;

	if (!(*stack = (char*)malloc(sizeof(char) * 100)))
		exit(EXIT_FAILURE);
	ft_memset(*stack, 0, 100);
	i = -1;
	if (*ins)
	{
		while ((*ins)[++i])
			st_tok(stack, (*ins)[i], 0);
		ft_strdel(ins);
	}
	i = -1;
	if (*str)
	{
		while ((*str)[++i])
			st_tok(stack, (*str)[i], 0);
		ft_strdel(str);
	}
}
