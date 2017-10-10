/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 18:40:57 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 21:39:13 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_tok	*stock_local(t_tok **lst, t_tok **sep, int i)
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

int		valid_local(t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;

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

t_tok	*valid_arg(t_tok **lst, t_ast **ast, t_tok **sep)
{
	t_tok	*tmp;
	t_ast	*tmp_ast;

	tmp = *lst;
	tmp_ast = *ast;
	if (valid_local(&tmp, sep))
	{
		stock_local(&tmp, sep, 1);
		return (NULL);
	}
	else
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
