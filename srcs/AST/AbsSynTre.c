/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbsSynTre.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 11:01:52 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/19 15:55:54 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	init_ast(t_ast **ast, char *str, int type)
{
	if (!(*ast = (t_ast*)malloc(sizeof(t_ast))))
	{
		*ast = NULL;
		return ;
	}
	(*ast)->str = str ? ft_strdup(str) : NULL;
	(*ast)->type = type;
	(*ast)->left = NULL;
	(*ast)->right = NULL;
}

typedef struct		s_type
{
	int				type;
	int				seq;
	void			(*f)(t_ast**, t_tok**, t_tok**);
}					t_type;



// t_ast	*creat_tree(t_tok **lst)
// {
// 	int						i;
// 	t_tok					*tmp;
// 	t_ast					*ast;
// 	t_ast					*tmp_ast;
// 	static const t_state	st[4] = {{QM, &qm_sequence}, {AND, &and_or},
// 			{OR, &and_or}, {PIPE, &pipe_sequence}};
//
// 	init_ast(&ast, 0);
// 	tmp_ast = ast;
// 	tmp = *lst; // Revoir assignation du node de reference
// 	while (tmp)
// 	{
// 		i = -1;
// 		while (++i < 4)
// 			if (st[i].type == tmp->type)
// 			{
// 				st[i].f(&tmp_ast, lst, &tmp);
// 				tmp_ast = tmp_ast->right;
// 				break ;
// 			}
// 		// i == 4 ? first_last_sequence(&tmp_ast, lst, &tmp) : 0; // PAS vraiment bon
// 		tmp = tmp->next;
// 	}
// }
