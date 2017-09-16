/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_pipe_seq.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 10:44:26 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/16 13:21:09 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_tok	*find_pipe_tok(t_tok **lst, t_tok **stop)
{
	t_tok	*tmp;

	tmp = *lst;
	while (tmp && tmp != *stop && (tmp->type != PIPE))
		tmp = tmp->n;
	return (tmp);
}

void			pipe_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_tok	*tmp_first;
	t_ast	*tmp_ast;

	tmp_ast = *ast;
	tmp_first = *lst;
	if ((tmp = find_pipe_tok(&tmp_first, sep)) != *sep)
	{
		init_ast(&tmp_ast->right, tmp->str, tmp->type);
		tmp_ast = tmp_ast->right;
		init_ast(&tmp_ast->left, NULL, CMD_SEQ);
		command_sequence(&tmp_ast->left, &tmp_first, &tmp);
		pipe_sequence(&tmp_ast, &tmp->n, sep);
	}
	else
	{
		init_ast(&tmp_ast->right, NULL, CMD_SEQ);
		command_sequence(&tmp_ast->right, lst, sep);
	}
}

void			simple_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_ast	*tmp_ast;

	tmp = *lst;
	tmp_ast = *ast;
	// while (tmp && tmp != *sep && tmp->str == LOCAL)
	// {
	// 	export(tmp->str, NULL, NULL, EXPORT);
	// 	tmp = tmp->next;
	// }
	// if (tmp != *sep)
	// {
		init_ast(&tmp_ast->left, tmp->str,
		ft_strrchr(tmp->str, '/') ? CMD_NAME_ABS : CMD_NAME_RLT);
		tmp = tmp->n;
		while (tmp != *sep)
		{
			init_ast(&tmp_ast->right, tmp->str, CMD_ARG);
			if (tmp->n != *sep)
				tmp_ast = tmp_ast->right;
			tmp = tmp->n;
		}
	// 	return (1);
	// }
	// return (-1);
}

void			command_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_ast	*tmp_ast;

	tmp = *lst;
	tmp_ast = *ast;
	while (tmp && (tmp->type == WORD || tmp->type == QUOTE ||
		tmp->type == DQUOTE || tmp->type == LOCAL))
		tmp = tmp->n;
	init_ast(&tmp_ast->left, NULL, SIMP_CMD);
	simple_sequence(&tmp_ast->left, lst, &tmp);
	if (tmp != *sep)
	{
		init_ast(&(*ast)->right, NULL, IO_SEQ);
		io_sequence(&(*ast)->right, &tmp, sep);
	}
}
