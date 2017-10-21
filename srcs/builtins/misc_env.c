/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 14:07:59 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/18 14:08:46 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	complete_node(t_env **node, char *env)
{
	char	*st;

	st = ft_strchr(env, '=');
	st[0] = '\0';
	(*node)->var = ft_strdup(env);
	(*node)->value = st + 1 ? ft_strdup(st + 1) : NULL;
	(*node)->next = NULL;
}

void	init_env_ast(t_ast **ast, char *str, int type)
{
	if (!(*ast = (t_ast*)malloc(sizeof(t_ast))))
		return ;
	(*ast)->right = NULL;
	(*ast)->left = NULL;
	(*ast)->str = str ? ft_strdup(str) : NULL;
	(*ast)->type = type;
}
