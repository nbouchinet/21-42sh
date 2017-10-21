/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 13:45:25 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/11 10:21:13 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	destroy_ast(t_ast **head)
{
	t_ast	*tmp;

	tmp = *head;
	if (!tmp)
		return ;
	tmp->left ? destroy_ast(&tmp->left) : 0;
	tmp->right ? destroy_ast(&tmp->right) : 0;
	tmp->str ? ft_strdel(&tmp->str) : 0;
	free(tmp);
	tmp = NULL;
}

void	destroy_tok(t_tok **head)
{
	t_tok	*tmp;
	t_tok	*save;

	tmp = *head;
	while (tmp)
	{
		save = tmp->n;
		ft_strdel(&tmp->str);
		tmp->hd != 0 ? close(tmp->hd) : 0;
		free(tmp);
		tmp = save;
	}
}
