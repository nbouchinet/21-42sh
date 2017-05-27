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

// typedef struct		s_lex
// {
// 	char			*ch;
// 	int				type;
// }					t_lex;

// int		cmp_sep(t_tok *tmp)
// {
// 	if (tmp->type == SPACE_TOK)
// 		tmp = tmp->next;
// 	if (tmp->type <= CHEVRON)
// 		return (1);
// 	return (0);
// }

// void 	specified_dir(t_tok **lst)
// {
// 	int				i;
// 	t_tok			*tmp;
// 	static const	t_lex	dir[6] = {{">", RDIR}, {"<", BDIR}, {">>", RRDIR},
// 					{"<<", BBDIR}, {">&", RDIR}, {"<&", BDIR}};
// 	tmp = *lst;
// 	while (tmp)
// 	{
// 		i = -1;
// 		if (tmp->type == CHEVRON)
// 			while (++i < 6)
// 			{
// 				if (ft_strcmp(dir[i].ch, tmp->str) == 0)
// 					tmp->type = dir[i].type;
// 			}
// 		tmp = tmp->next;
// 	}
// }

// int		lexer_check(t_tok **lst)
// {
// 	t_tok	*tmp;

// 	tmp = *lst;
// 	while (tmp)
// 	{
// 		if (tmp && tmp->next && (tmp->type <= CHEVRON))
// 			if (tmp->next && cmp_sep(tmp->next) == 1)
// 			{
// 				ft_errormsg("error: parsing near: ", NULL, tmp->str);
// 				return (-1);
// 			}
// 		tmp = tmp->next;
// 	}
// 	specified_dir(lst);
// 	return (0);
// }

static void		swap_link(t_tok	**lst)
{
	char		*save_str;
	int			save_type;

	save_str = NULL;
	while ((*lst) && (*lst)->type != QM)
	{
		save_str = (*lst)->str;
		save_type = (*lst)->type;
		
		(*lst)->str = n_type != 4 ? (*lst)->next->str : (*lst)->next->next->str;
		(*lst)->type = n_type != 4 ? (*lst)->next->type : (*lst)->next->next->type;

		(*lst)->next->str = save_str;
		(*lst)->next->type = save_type;
		(*lst) ? (*lst) = (*lst)->next : 0;
	}
	(*lst)->next ? (*lst) = (*lst)->next : 0;
}

void	lexer_check(t_tok **lst)
{
	t_tok	*tmp;

	tmp = *lst;
	while (tmp && tmp->next)
		if (tmp->next && (tmp->type == PIPE || tmp->type == AND || tmp->type == OR ||
		tmp->type == CHEVRON))
			tmp->type == PIPE || tmp->type == AND || tmp->type == OR ||
			(tmp->type == CHEVRON && tmp->next->type == CHEVRON) ?
			swap_db_link(&tmp) : swap_link(&tmp);
		else
			tmp->next ? tmp = tmp->next : 0;
}
