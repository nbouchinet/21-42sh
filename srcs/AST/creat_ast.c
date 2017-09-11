/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 10:33:27 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/11 17:50:02 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		init_next_node(t_ast **ast, t_tok **lst, t_tok **next)
{
	init_ast(&(*ast)->right, NULL, 0);
	(*ast) = (*ast)->right;
	(*lst) = (*next)->n;
}

void			primary_sequence(t_ast **ast, t_tok **lst)
{
	t_tok	*tmp;
	t_tok	*tmp_first;
	t_ast	*tmp_ast;

	tmp = *lst;
	tmp_first = *lst;
	tmp_ast = *ast;
	while (tmp)
	{
		if ((tmp = multi_qm(&tmp)))
		{
			tmp_ast->type = QM_SEQ;
			qm_sequence(&tmp_ast, &tmp_first, &tmp);
			if (tmp->n)
				init_next_node(&tmp_ast, &tmp_first, &tmp);
		}
		tmp ? (tmp = tmp->n) : 0;
	}
	tmp_ast->type == 0 ? secondary_sequence(&tmp_ast, &tmp_first, &tmp) : 0;
}

void			secondary_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_tok	*tmp_first;
	t_ast	*tmp_ast;

	tmp = *lst;
	tmp_ast = *ast;
	tmp_first = *lst;
	while (tmp && tmp != *sep)
	{
		if (tmp->type == AND || tmp->type == OR)
		{
			tmp_ast->type = AND_OR;
			oa_sequence(&tmp_ast, &tmp_first, sep);
			break ;
		}
		tmp = tmp->n;
	}
	if (tmp_ast->type == 0)
		tertiary_sequence(&tmp_ast, &tmp_first, sep);
}

void			tertiary_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_ast	*tmp_ast;

	tmp = *lst;
	tmp_ast = *ast;
	while (tmp && tmp != *sep)
	{
		if (tmp->type == BG)
		{
			tmp_ast->type = BG_SEQ;
			bg_sequence(&tmp_ast, lst, sep);
			break ;
		}
		tmp = tmp->n;
	}
	if (tmp_ast->type == 0)
		quaternary_sequence(&tmp_ast, lst, sep);
}

void			quaternary_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_ast	*tmp_ast;

	tmp = *lst;
	tmp_ast = *ast;
	while (tmp && tmp != *sep)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp_ast)
				init_ast(&tmp_ast, NULL, 0);
			tmp_ast->type = PIPE_SEQ;
			pipe_sequence(&tmp_ast, lst, sep);
			break ;
		}
		tmp = tmp->n;
	}
	if (tmp_ast->type == 0)
	{
		tmp_ast->type = CMD_SEQ;
		command_sequence(&tmp_ast, lst, sep);
	}
}
