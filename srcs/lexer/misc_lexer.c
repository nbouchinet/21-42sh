/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 15:30:01 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 19:22:59 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		print_error_lexer(t_tok **lst, t_tok **n, int mod)
{
	if (mod == 1)
		fd_printf(2, "parse error near unexpected token `%s'\n", (*lst)->str);
	else if (mod == 2)
		write(2, "parse error near unexpected token `newline'\n", 45);
	else if (mod == 3)
		fd_printf(2, "parse error near unexpected token `%s'\n", (*lst)->str);
	else if (mod == 4)
		fd_printf(2, "parse error near unexpected token `%s'\n", (*n)->str);
	return (1);
}

void	replace_tok(t_tok **start, t_tok **next, t_tok **sub, t_tok **sub_end)
{
	t_tok	*start2;
	t_tok	*next2;
	t_tok	*sub2;
	t_tok	*sub_end2;

	start2 = *start;
	next2 = *next;
	sub2 = *sub;
	sub_end2 = *sub_end;
	if (start2 != next2)
		start2->n = *sub;
	if (next2->type != IO_N)
		next2->n->n = sub_end2->n ? sub_end2->n : NULL;
	else
		next2->n->n->n = sub_end2->n ? sub_end2->n : NULL;
	sub_end2->n = next2;
}

void	swap_tok(t_tok **lst, t_tok **start, t_tok **next, t_tok **w)
{
	t_tok	*tmp;

	tmp = *w;
	while (tmp && tmp->n && (tmp->n->type & (WORD | LOCAL)))
		tmp = tmp->n;
	(*lst == *next) ? *lst = *w : 0;
	replace_tok(*start ? start : next, next, w, &tmp);
}
