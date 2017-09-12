/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_io_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 12:14:21 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/12 17:29:55 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_tok			*find_rdi_tok(t_tok **lst, t_tok **stop)
{
	t_tok	*tmp;

	tmp = *lst;
	if (tmp->type == IO_N)
		tmp = tmp->n->n;
	else
		tmp = tmp->n;
	while (tmp && tmp != *stop && tmp->type != IO_N && (tmp->type < RDIR ||
	tmp->type > BGRE))
		tmp = tmp->n;
	return (tmp);
}

static void		exec_else(t_tok *t_f, t_ast *t_a)
{
	init_ast(&t_a->right, t_f->type == IO_N ? t_f->str :
	NULL, t_f->type == IO_N ? t_f->n->type : t_f->type);
	t_a = t_a->right;
	init_ast(&t_a->left, t_f->type == IO_N ?
	t_f->n->n->str : t_f->n->str, FIL);
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
	io = NULL;
	while ((tmp = find_rdi_tok(&t_f, sep)) != *sep)
	{
		io = tmp->type == IO_N ? tmp : NULL;
		rdir = tmp->type == IO_N ? tmp->n : tmp;
		t_f = tmp->type == IO_N ? tmp->n->n : tmp->n;
	}
	if (t_f != *lst)
	{
		init_ast(&t_a->right, io ? io->str : NULL, io ?
		io->n->type : rdir->type);
		t_a = t_a->right;
		init_ast(&t_a->left, io ? io->n->n->str : rdir->n->str, FIL);
		io_sequence(&t_a, lst, io ? &io : &rdir);
	}
	else
		exec_else(t_f, t_a);
}
