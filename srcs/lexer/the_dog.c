/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_dog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:43:46 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/12 23:50:34 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	complete_quote(char **stack, char *line, int *i, char quote)
{
	// if (ft_strlen(*stack) > 0 && quote == '"')
	// 	stack_expanse(stack);

	while (line[(*i)] && line[(*i)] != quote)
	{
		if (quote == '"' && line[(*i)] == '\\')
		{
			st_tok(stack, line[++(*i)], 0);
			(*i)++;
		}
		else
			st_tok(stack, line[(*i)++], 0);
	}
	ft_putendl(*stack);
	(*i)++;
	if (quote == '"')
	{
		ft_putendl("WUT");
		ft_putendl(*stack);
		stack_expanse(stack);
	}
	else
	{
		ft_printf("quote == %c\n", quote);
		ft_putendl("========");
		ft_putstr("[");ft_putstr(*stack);ft_putendl("]");
		ft_putendl("========");
	}
}
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

void	backslash(t_tok **lst, char **stack, char *line, int *i)
{
	(void)lst;
	if (line[(*i) + 1])
		st_tok(stack, line[++(*i)], 0);
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
		tmp[i + 1] = c;
		ft_strdel(stack);
		*stack = tmp;
		len += 100;
	}
	else
		(*stack)[i] = c;
}
