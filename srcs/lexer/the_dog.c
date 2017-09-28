/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_dog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:43:46 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/28 15:02:58 by khabbar          ###   ########.fr       */
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

void	st_tok(char **stack, char c, int reset)
{
	static int		len = 100;
	int				i;
	char			*tmp;


	i = 0;
	if (reset)
	{
		len = 100;
		return ;
	}
	if ((i = (int)ft_strlen(*stack)) == (len - 1))
	{
		i = -1;
		if (!(tmp = (char *)malloc(sizeof(char) * (len + 100))))
			exit (0);
		ft_memset(tmp, 0, (len + 100));
		while ((*stack)[++i])
			tmp[i] = (*stack)[i];
		tmp[i + 1] = c;
		ft_strdel(stack);
		*stack = tmp;
		len += 100;
	}
	else
		(*stack)[i] = c;
}
