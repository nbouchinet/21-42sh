/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/02 16:52:22 by zadrien           #+#    #+#             */
/*   Updated: 2017/07/02 17:13:39 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"

void	check_var(t_tok **lst, t_env **env)
{
	int		i;
	int		j;
	t_tok	*tmp;

	i = -1;
	tmp = *lst;
	while (tmp->str[++i])
	{
		if (tmp->str[i] == '$')
		{
			j = 0;
			while (tmp->str[i + j] && tmp->str[i + j] != ' ')
				j++;
		}
	}
}

void	check_expanse(t_tok **lst, t_env **env)
{
	t_tok	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->type != QUOTE)
			check_var(&tmp, env);
		tmp = tmp->next;
	}
}
