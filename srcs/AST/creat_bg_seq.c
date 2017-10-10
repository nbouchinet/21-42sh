/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_bg_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 13:26:25 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 15:17:29 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_tok	*find_bg_tok(t_tok **lst, t_tok **stop)
{
	t_tok	*tmp;

	tmp = *lst;
	while (tmp && tmp != *stop && (tmp->type != BGE))
		tmp = tmp->n;
	return (tmp);
}

void			bg_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_ast	*tmp_ast;

	tmp_ast = *ast;
	if ((tmp = find_bg_tok(lst, sep)) != *sep)
	{
		init_ast(&tmp_ast->right, &tmp, tmp->type);
		tmp_ast = tmp_ast->right;
		init_ast(&tmp_ast->left, NULL, 0);
		quaternary_sequence(&tmp_ast->left, lst, &tmp);
		if (tmp->n != NULL)
			bg_sequence(&tmp_ast, &tmp->n, sep);
	}
	else
	{
		init_ast(&tmp_ast->right, NULL, 0);
		quaternary_sequence(&tmp_ast->right, lst, sep);
	}
}
