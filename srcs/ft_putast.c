/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:01:19 by nmougino          #+#    #+#             */
/*   Updated: 2017/06/04 17:42:10 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>


void	free_ast(t_ast **ast)
{
	t_ast *tmp;

	tmp = *ast;
	if (tmp)
	{
		if (tmp->left)
		{

			free_ast(&tmp->left);
			// tmp->left->str ? ft_strdel(&tmp->left->str) : 0;
			ft_printf("%d><%d\n", tmp->type, tmp->left->type);
			ft_putendl("HI");
			tmp->right != NULL ? free(tmp->right) : 0;
			ft_putendl("OK");
			tmp->left = NULL;
		}
		if (tmp->right)
		{
			free_ast(&tmp->right);
			tmp->right->str ? ft_strdel(&tmp->right->str) : 0;
			ft_putendl("HO");
			tmp->right != NULL? free(tmp->right) : 0;
			ft_putendl("IK");
			tmp->right = NULL;
		}
		tmp->str ? ft_strdel(&tmp->str) : 0;
		free(tmp);
		tmp = NULL;
	}
}

static void	ft_rec_putbtreestr(t_ast *r, int l)
{
	if (r)
	{
		printf("t: %d |%s|\n", r->type, r->str);
		if (r->left)
		{
			printf("%*c|-left--: ", (l + 1) * 2, ' ');
			ft_rec_putbtreestr(r->left, l + 1);
		}
		if (r->right)
		{
			printf("%*c|-right-: ", (l + 1) * 2, ' ');
			ft_rec_putbtreestr(r->right, l + 1);
		}
	}
}

void		ft_putast(t_ast *root)
{
	ft_rec_putbtreestr(root, 0);
}
