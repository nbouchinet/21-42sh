/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:55:10 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/24 13:25:14 by zadrien          ###   ########.fr       */
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
	(*ast)->str = str ? ft_strdup(str) : NULL;
	(*ast)->type = type;
	(*ast)->left = NULL;
	(*ast)->right = NULL;
}

void	primary_sequence(t_ast **ast, t_tok **lst)
{
	t_tok	*tmp;
	t_tok	*tmp_first;
	t_ast	*tmp_ast;

	tmp = *lst;
	tmp_ast = *ast;
	tmp_first = *lst;
	while (tmp)
	{
		if (tmp->type == QM)
		{
			secondary_sequence(&tmp_ast, &tmp_first, &tmp);
			if (tmp->next)
			{
				init_ast(&tmp_ast->right, NULL, 0);
				tmp_ast = tmp_ast->right;
				tmp_first = tmp->next;
			}
		}
		tmp = tmp->next;
	}
	if (tmp_ast->type == 0)
		secondary_sequence(&tmp_ast, &tmp_first, &tmp);
	tmp_ast->right = NULL;
}

void	secondary_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok					*tmp;
	t_tok					*tmp_first;
	t_ast					*tmp_ast;

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
		tmp = tmp->next;
	}
	if (tmp_ast->type == 0)
		tertiary_sequence(&tmp_ast, &tmp_first, sep);
}

void	tertiary_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
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
			break;
		}
		tmp = tmp->next;
	}
	if (tmp_ast->type == 0)
	{
		//init_ast(&tmp_ast->left, NULL, CMD_SEQ)
		tmp_ast->type = CMD_SEQ;
		command_sequence(&tmp_ast, lst, sep);
	}
} // Stable and Working
