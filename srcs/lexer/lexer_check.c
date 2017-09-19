/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 16:38:18 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/19 17:26:55 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int				cmp_sep(t_tok *tmp)
{
	if (tmp->type == SPACE_TOK)
		tmp = tmp->n;
	if (tmp->type <= CHEVRON)
		return (1);
	return (0);
}

void			specified_dir(t_tok **lst)
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

static int		check_lst(t_tok **lst)
{
	t_tok		*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->type == CHEVRON && !tmp->n)
			return (write(2, "parse error near unexpected token `newline'\n",
			45));
		else if (tmp->type == CHEVRON && (tmp->n->str[0] == '<'
		|| tmp->n->str[0] == '&' || tmp->n->str[0] == ';'
		|| tmp->n->str[0] == '>' || tmp->n->str[0] == ')'
		|| tmp->n->str[0] == '|'))
			return (fd_printf(2, "parse error near unexpected token `%s'\n",
			tmp->str));
		else if ((tmp->type == QM && tmp->n && tmp->n->type == QM) ||
		(tmp == *lst && tmp->type == QM && !tmp->n))
			return (fd_printf(2,
				"parse error near unexpected token `newline'\n"));
		else
			tmp = tmp->n;
	}
	return (0);
}

static int		loop(t_tok **lst, t_tok **command)
{
	t_tok		*save_lst;
	t_tok		*save_next;
	t_tok		*save_last;

	save_lst = (*lst);
	save_last = NULL;
	save_next = NULL;
	while ((*lst)->type != WORD)
		if ((*lst)->type == CHEVRON)
		{
			(*lst) = (*lst)->n;
			if ((*lst)->n && ((*lst)->n->type != QM && (*lst)->n->type != AND &&
			(*lst)->n->type != OR && (*lst)->n->type != PIPE) && (*lst)->n->type != IO_N)
			{
				(*lst)->n->type != CHEVRON ? save_last = (*lst) : 0;
				(*lst) = (*lst)->n;
				save_last ? save_last->n = NULL : 0;
			}
			else
				return (0);
		}
		else
			(*lst) = (*lst)->n;
	(*command)->n = (*lst);
	while ((*lst)->n && (*lst)->n->type == WORD)
		(*lst) = (*lst)->n;
	save_next = (*lst)->n;
	(*lst)->n = save_lst;
	save_last->n = save_next;
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
	start2->n = *sub;
	if (next2->type != IO_N)
		next2->n->n = sub_end2->n ? sub_end2->n : NULL;
	else
		next2->n->n->n = sub_end2->n ? sub_end2->n : NULL;
	sub_end2->n = next2;
}

void	check_rdir(t_tok **start, t_tok **next)
{
	t_tok	*tmp;
	t_tok	*tmp2;
	t_tok	*sub;
	t_tok	*sub_end;

	tmp = *start;
	while (tmp)
	{
		if (tmp->type == IO_N)
		{
			if (tmp->n && tmp->n->type == CHEVRON)
				if (tmp->n->n && tmp->n->n->type == WORD)
					if (tmp->n->n->n && tmp->n->n->n->type == WORD)
					{
						sub = tmp->n->n->n;
						tmp2 = tmp->n->n->n;
						while (tmp2 && tmp2->n && tmp2->n->type == WORD)
							tmp2 = tmp2->n;
						sub_end = tmp2;
						replace_tok(start, next, &sub, &sub_end);
					}
		}
		else if (tmp->type == CHEVRON)
		{
			if (tmp->n && tmp->n->type == WORD)
				if (tmp->n->n && tmp->n->n->type == WORD)
				{
					sub = tmp->n->n;
					tmp2 = tmp->n->n;
					while (tmp2 && tmp2->n && tmp2->n->type == WORD)
						tmp2 = tmp2->n;
					sub_end = tmp2;
					replace_tok(start, next, &sub, &sub_end);
				}
		}
		tmp = tmp->n;
	}
}

void	restruct_lst(t_tok **lst)
{
	t_tok	*tmp;
	t_tok	*save;

	if (*lst)
	{
		tmp = *lst;
		while (tmp)
		{
			if (tmp->n && (tmp->n->type == CHEVRON || tmp->n->type == IO_N))
			{
				save = tmp;
				check_rdir(&save, &tmp->n);
			}
			tmp = tmp->n;
		}
	}
}

void			lexer_check(t_tok **lst)
{
	t_tok	*tmp;
	t_tok	*save_addr;

	tmp = *lst;
	save_addr = NULL;
	if (check_lst(lst) != 0)
	{
		delete_lst(lst);
		return ;
	}
	while (tmp)
	{
		if (tmp->type == CHEVRON || tmp->type == IO_N)
			loop(&tmp, &save_addr) ? tmp = (*lst) : 0;
		// else if (tmp->type == LOCAL && ((tmp->n && tmp->n->type != WORD) || !tmp->n))
		// 	tmp->type = WORD;
		else
		{
			save_addr = tmp;
			tmp = tmp->n;
		}
	}
}
