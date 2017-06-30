/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_io_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 12:14:21 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/30 18:50:07 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_tok	*find_rdir_tok(t_tok **lst, t_tok **stop, t_tok **io_n,
	t_tok **rdir)
{
	t_tok	*tmp;

	tmp = *lst;
	if (tmp->type == IO_N)
		tmp = tmp->n->n;
	else
		tmp = tmp->n;
	while (tmp && tmp != *stop && tmp->type != IO_N &&
		(tmp->type < RDIR || tmp->type > BGRE))
		tmp = tmp->n;
	if (tmp == *stop)
		return (tmp);
	(*io_n) = (tmp->type == IO_N ? tmp : NULL);
	(*rdir) = (tmp->type == IO_N ? tmp->n : tmp);
	(*lst) = (tmp->type == IO_N ? tmp->n->n : tmp->n);
	return (tmp);
}

static void		init_io(t_tok **lst, t_ast **ast, t_tok **io, t_tok **rdir)
{
	init_ast(&(*ast)->right, io ? (*io)->str : NULL, io ?
		(*io)->n->type : (*rdir)->type);
	(*ast) = (*ast)->right;
	init_ast(&(*ast)->left, io ?
		(*io)->n->n->str : (*rdir)->n->str, FIL);
	io_sequence(ast, lst, io ? io : rdir);
}

static void		init_last_io(t_tok **lst, t_ast **ast)
{
	init_ast(&(*ast)->right, (*lst)->type == IO_N ?
		(*lst)->str : NULL, (*lst)->type == IO_N ?
			(*lst)->n->type : (*lst)->type);
	(*ast) = (*ast)->right;
	init_ast(&(*ast)->left, (*lst)->type == IO_N ?
		(*lst)->n->n->str : (*lst)->n->str, FIL);
}

void			io_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_tok	*rdir;
	t_tok	*io;
	t_tok	*t_f;
	t_ast	*t_a;

	t_f = *lst;
	t_a = *ast;
	while ((tmp = find_rdir_tok(&t_f, sep, &io, &rdir)) != *sep)
		;
	if (t_f != *lst)
		init_io(&t_f, &t_a, &io, &rdir);
	else
		init_last_io(&t_f, &t_a);
}
