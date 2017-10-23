/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 18:40:57 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 12:04:23 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_tok		*stock_local(t_tok **lst, t_tok **sep, int i)
{
	t_tok	*tmp;

	tmp = *lst;
	while (tmp && (tmp->type & LOCAL) && tmp != *sep)
	{
		if (i)
			local(tmp->str);
		tmp = tmp->n;
	}
	return (tmp);
}

static int			valid_local(t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	int		i;

	i = -1;
	if (*lst)
	{
		tmp = *lst;
		while (tmp && tmp != *sep)
		{
			if (tmp->type != LOCAL)
				return (0);
			tmp = tmp->n;
		}
	}
	return (1);
}

static int			check_tmp(t_tok *tmp)
{
	int		i;

	i = -1;
	while (tmp->str[++i] != '=')
	{
		if (tmp->str[i] == '_')
			continue ;
		if (ft_isalnum(tmp->str[i]) == 0)
			break ;
	}
	if (tmp->str[i] != '=')
		return (0);
	return (1);
}

t_tok				*valid_arg(t_tok **lst, t_ast **ast, t_tok **sep)
{
	t_tok	*tmp;
	t_ast	*tmp_ast;
	int		j;

	tmp = *lst;
	tmp_ast = *ast;
	j = -1;
	if (valid_local(&tmp, sep))
	{
		if (check_tmp(tmp))
		{
			stock_local(&tmp, sep, 1);
			return (NULL);
		}
	}
	else if (check_tmp(tmp))
	{
		if ((tmp = stock_local(&tmp, sep, 0)) == *sep)
			return (NULL);
	}
	if (ft_strchr(tmp->str, '/'))
		init_ast(&tmp_ast->left, &tmp, CMD_NAME_ABS);
	else
		init_ast(&tmp_ast->left, &tmp, CMD_NAME_RLT);
	return (tmp->n);
}
