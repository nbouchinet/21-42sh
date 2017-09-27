/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_dog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:43:46 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/27 18:56:17 by zadrien          ###   ########.fr       */
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
	word[1] = '\0';
	ft_putendl("1.2");
	if (ft_strlen(*stack) >= len)
	{
		ft_putendl("1.3");
		ft_putendl(*stack);
		tmp = ft_strdup(*stack);

		ft_strdel(stack);
		ft_putendl("1.5");
		if (!((*stack) = ft_memalloc(len + 100)))
			exit(fd_printf(2, "malloc error\n"));
		ft_putendl("1.6");
		ft_putendl(tmp);
		ft_strcpy((*stack), tmp);
		ft_putendl("1.7");
		ft_strcat((*stack), word);
		ft_putendl("1.8");
		free(tmp);
		ft_putendl("1.9");
		len += 100;
	}
	else
		ft_strcat((*stack), word);
}
