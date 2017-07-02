/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 16:38:18 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/30 19:16:32 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		cmp_sep(t_tok *tmp)
{
	if (tmp->type == SPACE_TOK)
		tmp = tmp->n;
	if (tmp->type <= CHEVRON)
		return (1);
	return (0);
}

void	specified_dir(t_tok **lst)
{
	int				i;
	t_tok			*tmp;
	static const	t_lex	dir[6] = {{">", RDIR}, {"<", BDIR}, {">>", RRDIR},
					{"<<", BBDIR}, {">&", AGRE}, {"<&", BGRE}};
	tmp = *lst;
	while (tmp)
	{
		i = -1;
		if (tmp->type == CHEVRON)
			while (++i < 6)
			{
				if (ft_strcmp(dir[i].ch, tmp->str) == 0)
					tmp->type = dir[i].type;
			}
		tmp = tmp->n;
	}
}

static int		check_lst(t_tok **lst)
{
	t_tok		*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->type == CHEVRON && (tmp->n->str[0] == '<'
		|| tmp->n->str[0] == '&' || tmp->n->str[0] == ';'
		|| tmp->n->str[0] == '>' || tmp->n->str[0] == ')'
		|| tmp->n->str[0] == '|'))
			return (fd_printf
			(2, "parse error near unexpected token `%s'\n", tmp->str));
		else if ((tmp->type == QM && tmp->n && tmp->n->type == QM) ||
		(tmp == *lst && tmp->type == QM && !tmp->n))
			return (fd_printf
			(2, "parse error near unexpected token `newline'\n"));
		else
			tmp = tmp->n;
	}
	return (0);
}

static int		check(t_tok **lst)
{
	t_tok		*tmp;
	int			i;

	tmp = *lst;
	i = 0;
	while (tmp->n)
	{
		if (tmp->type == CHEVRON)
		{
			i = 1;
			tmp->n ? tmp = tmp->n : 0;
			if (tmp->n)
				tmp = tmp->n;
			else
				break ;
			continue ;
		}
		i = (tmp->type == QM || tmp->type == AND || tmp->type == OR ? 0 : i);
		if (i && tmp->type == WORD)
			return (1);
		tmp->n ? tmp = tmp->n : 0;
		if (!tmp->n)
			break ;
	}
	return (0);
}

static void		loop(t_tok **lst, t_tok **tmp)
{
	char		*save_str;
	int			save_type;

	save_str = NULL;
	save_type = 0;
	ft_putendl((*lst)->n->str);
	ft_putnbrl((*lst)->n->type);
	while ((*lst)->n && (*lst)->n->type != QM)
	{
		save_str = (*lst)->str;
		save_type = (*lst)->type;
		(*lst)->str = (*lst)->n->str;
		(*lst)->type = (*lst)->n->type;
		(*lst)->n->str = save_str;
		(*lst)->n->type = save_type;
		!(*tmp) ? (*tmp) = (*lst) : 0;
		(*lst)->n ? (*lst) = (*lst)->n : 0;
	}
}

void			lexer_check(t_tok **lst)
{
	t_tok	*tmp;
	t_tok	*save_addr;

	tmp = *lst;
	if (check_lst(lst) != 0)
	{
		delete_lst(lst);
		return ;
	}
	while (tmp->n)
	{
		if (tmp->type == CHEVRON)
		{
			save_addr = NULL;
			loop(&tmp, &save_addr);
			save_addr ? loop(&save_addr, &save_addr) : 0;
		}
		else
			tmp->n ? tmp = tmp->n : 0;
	}
	if (check(lst))
		lexer_check(lst);
	specified_dir(lst);
}
