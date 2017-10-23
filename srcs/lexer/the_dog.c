/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_dog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:43:46 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 12:23:19 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		is_sep(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&' || c == ';')
		return (1);
	return (0);
}

void	backslash(t_tok **lst, char **stack, char *line, int *i)
{
	(void)lst;
	if (line[(*i) + 1])
		st_tok(stack, line[++(*i)], 0);
	else if (line[(*i) + 1])
		(*i)++;
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
			exit(0);
		ft_memset(tmp, 0, (len + 100));
		while ((*stack)[++i])
			tmp[i] = (*stack)[i];
		tmp[i] = c;
		ft_strdel(stack);
		*stack = tmp;
		len += 100;
	}
	else
		(*stack)[i] = c;
}
