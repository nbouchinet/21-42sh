/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oa_sequence.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 05:51:37 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/24 14:00:53 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_tok	*find_andor_tok(t_tok **lst, t_tok **stop)
{
	t_tok	*tmp;

	tmp = *lst;
	while (tmp && tmp != *stop && (tmp->type != AND && tmp->type != OR))
		tmp = tmp->next;
	return (tmp);
}


void	oa_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_tok	*tmp_first;
	t_tok	*new_sep;
	t_ast	*tmp_ast;

	tmp_ast = *ast;
	tmp_first = *lst;
	while ((tmp = find_andor_tok(&tmp_first, sep)) != *sep)
	{
		tmp_first = tmp->next;
		new_sep = tmp;
		tmp = tmp->next;
	}
	if (tmp_first != *lst)
	{
		init_ast(&tmp_ast->left, new_sep->str, new_sep->type);
		tmp_ast = tmp_ast->left;
		init_ast(&tmp_ast->right, NULL, 0);
		tertiary_sequence(&tmp_ast->right, &tmp_first, &tmp); // GEstion PIPE dans command_sequence()
		oa_sequence(&tmp_ast, lst, &new_sep);
	}
	else
	{
		init_ast(&tmp_ast->left, NULL, 0);
		tertiary_sequence(&tmp_ast->left, lst, sep);
	}
} // Actually Work
