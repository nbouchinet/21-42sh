/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 15:24:18 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/27 15:04:07 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_export(t_ast **ast, t_env **env)
{
	t_local   *loc;
	t_env     *tmp;

	(*ast)->right ? io_seq(&(*ast)->right->right) : 0;
	loc = *local_slg(0);
	tmp = *env;
	if (!loc || !(*ast)->left->right->str || !*env)
		return (0);
	while (loc && ft_strcmp(loc->var, (*ast)->left->right->str))
		loc = loc->n;
	if (!loc)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = (t_env *)malloc(sizeof(t_env))))
		exit(fd_printf(2, "malloc error\n"));
	tmp->next->var = ft_strdup(loc->var);
	tmp->next->value = ft_strdup(loc->val);
	tmp->next->next = NULL;
	return (1);
}
