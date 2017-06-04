/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_sequence.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 16:41:40 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/04 16:21:00 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_tok	*find_rdir_tok(t_tok **lst, t_tok **stop)
{
	t_tok	*tmp;

	tmp = *lst;
	if (tmp->type == IO_N)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	while (tmp && tmp != *stop && tmp->type != IO_N && (tmp->type < RDIR || tmp->type > BGRE))
	{
		ft_putendl(tmp->str);
		tmp = tmp->next;
	}
	return (tmp);
}

void	io_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_tok	*rdir;
	t_tok	*io_numb;
	t_tok	*t_f;
	t_ast	*tmp_ast;

	t_f = *lst;
	io_numb = NULL;
	tmp_ast = *ast;
	while ((tmp = find_rdir_tok(&t_f, sep)) != *sep)
	{
		io_numb = tmp->type == IO_N ? tmp : NULL;
		rdir = tmp->type == IO_N ? tmp->next : tmp;
		t_f = tmp->type == IO_N ? tmp->next->next : tmp->next;
	}
	if (t_f != *lst)
	{
		init_ast(&tmp_ast->left, io_numb ? io_numb->str : NULL, io_numb ? io_numb->next->type : rdir->type);
		tmp_ast =tmp_ast->left;
		init_ast(&tmp_ast->right, io_numb ? io_numb->next->next->str : rdir->next->str, FILENAME);
		io_sequence(&tmp_ast, lst, io_numb ? &io_numb : &rdir);
	}
	else
	{
		init_ast(&tmp_ast->left, t_f->type == IO_N ? t_f->str : NULL, t_f->type == IO_N ? t_f->next->type : t_f->type);
		tmp_ast = tmp_ast->left;
		init_ast(&tmp_ast->right, t_f->type == IO_N ? t_f->next->next->str : t_f->next->str, FILENAME);
	}
}
