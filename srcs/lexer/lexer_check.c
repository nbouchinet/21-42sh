/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 16:38:18 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/18 09:09:34 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		error_lexer(t_tok **p, t_tok **tmp, t_tok **n)
{
	if (!(*p) && ((*tmp)->type & (AND | OR | QM | PIPE | BGE)))
		return (print_error_lexer(tmp, n, 1));
	else if (!(*n) && ((*tmp)->type & CHEVRON))
		return (print_error_lexer(NULL, NULL, 2));
	else if (!(*n) && !((*tmp)->type & (BGE | QM)))
		return (print_error_lexer(tmp, n, 3));
	else if ((*n) && (*n)->type & (AND | OR | BGE | CHEVRON | QM | PIPE | IO_N))
		return (print_error_lexer(NULL, n, 4));
	return (0);
}

int		new_lexercheck(t_tok **lst)
{
	t_tok	*tmp;
	t_tok	*prev;

	prev = NULL;
	if (*lst)
	{
		tmp = *lst;
		while (tmp)
		{
			if (tmp->type & (PIPE | QM | AND | OR | CHEVRON | BGE))
				if (error_lexer(&prev, &tmp, &tmp->n))
					return (0);
			prev = tmp;
			tmp = tmp->n;
		}
	}
	return (1);
}

void	specified_dir(t_tok **lst)
{
	int					i;
	t_tok				*tmp;
	static const t_lex	dir[6] = {{">", RDIR}, {"<", BDIR}, {">>", RRDIR},
								{"<<", BBDIR}, {">&", AGRE}, {"<&", BGRE}};

	tmp = *lst;
	while (tmp)
	{
		i = -1;
		if (tmp->type == CHEVRON)
			while (++i < 6)
				if (ft_strcmp(dir[i].ch, tmp->str) == 0)
					tmp->type = dir[i].type;
		tmp = tmp->n;
	}
}

void	check_rdir(t_tok **lst, t_tok **start, t_tok **next)
{
	t_tok	*tmp;

	tmp = *next;
	if (tmp->type & IO_N)
	{
		if (tmp->n && tmp->n->type == CHEVRON)
			if (tmp->n->n && tmp->n->n->type == WORD)
				if (tmp->n->n->n && tmp->n->n->n->type == WORD)
					swap_tok(lst, start, next, &tmp->n->n->n);
	}
	else if (tmp->type == CHEVRON)
	{
		if (tmp->n && tmp->n->type == WORD)
			if (tmp->n->n && tmp->n->n->type == WORD)
				swap_tok(lst, start, next, &tmp->n->n);
	}
}

void	restruct_lst(t_tok **lst)
{
	t_tok	*tmp;
	t_tok	*prev;

	if (*lst)
	{
		prev = *lst;
		tmp = *lst;
		while (tmp)
		{
			if (tmp && (tmp->type & (CHEVRON | IO_N)))
				check_rdir(lst, &prev, &tmp);
			prev = tmp;
			tmp = tmp->n;
		}
	}
}
