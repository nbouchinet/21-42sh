/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 16:11:19 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/16 13:32:39 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	find_var(char *var, char **stack)
{
	int		i;
	t_local	*loc;
	t_env	*env;

	i = -1;
	if ((loc = find_local(local_slg(0), var)))
	{
		while (loc->val[++i])
			st_tok(stack, loc->var[i], 0);
	}
	else if ((env = find_node(&(*cmdl_slg())->lstenv, var, NULL)))
	{
		while (env->value[++i])
			st_tok(stack, env->value[i], 0);
	}
}

void	expanse_stack(char **stack, char *line, int *i)
{
	int		j;
	char	*str;

	j = (*i) += 1;
	if (line[j] == ' ' || line[j] == '\0' || line[j] == '\'' || line[j] == '"')
		st_tok(stack, line[j - 1], 0);
	else
	{
		while (line[(*i)] && !is_space(line[(*i)]) &&
				line[(*i)] != '"' && line[(*i)] != '\'')
			(*i)++;
		str = ft_strsub(line, j, (*i) - j);
		find_var(str, stack);
		ft_strdel(&str);
	}
}

void	in_quote(char **stack, char *line, int *i, char type)
{
	while (line[(*i)] && line[(*i)] != type)
	{
		if (type == '"' && line[(*i)] == '\\')
		{
			st_tok(stack, line[++(*i)], 0);
			(*i)++;
		}
		else if (type == '"' && line[(*i)] == '$')
			expanse_stack(stack, line, i);
		else
			st_tok(stack, line[(*i)++], 0);
	}
	(*i)++;
}

void	after_quote(char **stack, char *line, int *i)
{
	while (line[(*i)] && !is_space(line[(*i)]) &&
			line[(*i)] != '"' && line[(*i)] != '\'')
	{
		if (line[(*i)] == '\\')
		{
			st_tok(stack, line[++(*i)], 0);
			(*i)++;
		}
		else if (line[(*i)] == '$')
			expanse_stack(stack, line, i);
		else
			st_tok(stack, line[(*i)++], 0);
	}
}
