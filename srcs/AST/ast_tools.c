/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 17:11:46 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/30 18:49:31 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_ast(t_ast **ast, char *str, int type)
{
	if (!(*ast = (t_ast*)malloc(sizeof(t_ast))))
	{
		*ast = NULL;
		return ;
	}
	if (str)
		(*ast)->str = ft_strdup(str);
	else
		(*ast)->str = NULL;
	(*ast)->type = type;
	(*ast)->left = NULL;
	(*ast)->right = NULL;
}

t_tok	*multi_qm(t_tok **lst)
{
	t_tok	*tmp;
	t_tok	*new_sep;
	t_tok	*tmp_first;

	tmp = *lst;
	tmp_first = *lst;
	new_sep = NULL;
	while ((tmp = find_q_tok(&tmp_first)))
	{
		tmp_first = tmp->n;
		new_sep = tmp;
		tmp = tmp->n;
	}
	return (new_sep);
}

t_tok	*find_q_tok(t_tok **lst)
{
	t_tok	*tmp;

	tmp = *lst;
	while (tmp && (tmp->type != QM))
		tmp = tmp->n;
	return (tmp);
}
