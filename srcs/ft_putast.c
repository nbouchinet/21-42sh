/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:01:19 by nmougino          #+#    #+#             */
/*   Updated: 2017/05/24 17:10:11 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

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
