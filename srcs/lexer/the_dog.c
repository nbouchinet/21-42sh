/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_dog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:43:46 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/23 20:00:38 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parser.h"

void	delete_lst(t_tok **cmd)
{
	t_tok *tmp;

	while ((*cmd))
	{
		tmp = *cmd;
		(*cmd) = (*cmd)->next;
		ft_strdel(&tmp->str);
		free(tmp);
	}
}

void	st_tok(char **stack, char c)
{
	int		i;

	i = ft_strlen(*stack);
	(*stack)[i] = c;
}
