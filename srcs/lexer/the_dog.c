/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_dog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:43:46 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/13 12:09:44 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	delete_lst(t_tok **cmd)
{
	t_tok *tmp;

	while ((*cmd))
	{
		tmp = *cmd;
		(*cmd) = (*cmd)->n;
		ft_strdel(&tmp->str);
		free(tmp);
	}
	*cmd = NULL;
}

void	st_tok(char **stack, char c)
{
	char			word[2];
	char			*tmp;
	static size_t	len = 100;

	word[0] = c;
	word[1] = 0;
	if (ft_strlen(*stack) >= len)
	{
		tmp = (*stack);
		if (!((*stack) = ft_memalloc(len + 100)))
			exit(fd_printf(2, "malloc error\n"));
		(*stack) = ft_strcpy((*stack), tmp);
		(*stack) = ft_strcat((*stack), word);
		free(tmp);
		len += 100;
	}
	else
		ft_strcat((*stack), word);
}
