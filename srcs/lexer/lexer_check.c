/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 16:38:18 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/24 13:24:36 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

typedef struct		s_lex
{
	char			*ch;
	int				type;
}					t_lex;

int		cmp_sep(t_tok *tmp)
{
	if (tmp->type == SPACE_TOK)
		tmp = tmp->next;
	if (tmp->type <= CHEVRON)
		return (1);
	return (0);
}

void 	specified_dir(t_tok **lst)
{
	int				i;
	t_tok			*tmp;
	static const	t_lex	dir[6] = {{">", RDIR}, {"<", BDIR}, {">>", RRDIR},
					{"<<", BBDIR}, {">&", RDIR}, {"<&", BDIR}};
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
		tmp = tmp->next;
	}
}

static int		check_lst(t_tok **lst)
{
	t_tok		*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->type == CHEVRON && (tmp->str[0] == '<' || tmp->str[0] == '&' ||
		tmp->str[0] == ';' || tmp->str[0] == '>' || tmp->str[0] == ')' ||
		tmp->str[0] == '|'))
			return (fd_printf
			(2, "parse error near unexpected token `%s'\n", tmp->str));
		else if ((tmp->type == QM && tmp->next && tmp->next->type == QM) ||
		(tmp == *lst && tmp->type == QM && !tmp->next))
			return (fd_printf
			(2, "parse error near unexpected token `newline'\n"));
		else
			tmp = tmp->next;
	}
	return (0);
}

static void		loop(t_tok **lst, t_tok **tmp)
{
	char		*save_str;
	int			save_type;

	save_str = NULL;
	save_type = 0;
	while ((*lst)->next && (*lst)->next->type != QM)
	{
		save_str = (*lst)->str;
		save_type = (*lst)->type;
		(*lst)->str = (*lst)->next->str;
		(*lst)->type = (*lst)->next->type;
		(*lst)->next->str = save_str;
		(*lst)->next->type = save_type;
		!(*tmp) ? (*tmp) = (*lst) : 0;
		(*lst)->next ? (*lst) = (*lst)->next : 0;
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
	while (tmp && tmp->next)
	{
		if (tmp->type == CHEVRON)
		{
			save_addr = NULL;
			loop(&tmp, &save_addr);
			save_addr ? loop(&save_addr, &save_addr) : 0;
		}
		else
			tmp->next ? tmp = tmp->next : 0;
	}
	specified_dir(lst);
}
