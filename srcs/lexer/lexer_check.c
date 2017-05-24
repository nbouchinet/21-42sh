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

int		lexer_check(t_tok **lst)
{
	t_tok	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp && tmp->next && (tmp->type <= CHEVRON))
			if (tmp->next && cmp_sep(tmp->next) == 1)
			{
				ft_errormsg("error: parsing near: ", NULL, tmp->str);
				return (-1);
			}
		tmp = tmp->next;
	}
	specified_dir(lst);
	return (0);
}
