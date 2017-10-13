/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_dog.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:43:46 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/13 22:30:27 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	complete_quote(char **stack, char *line, int *i, char quote)
{
	if (ft_strlen(*stack) > 0 && quote == '"')
	{
		// ft_printf("[%c] First expanse complete_quote\n", quote);
		stack_expanse(stack);
	}
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
	// ft_printf("%@complete_quote: %s%@\n", BLUE, *stack, I);
	// if (line[(*i) + 1])
	// 	(*i)++; I"M IN THE QUOTE
	if (quote == '"')
	{
		// ft_putendl("complete_quote: DQUOTE");
		stack_expanse(stack);
		// ft_printf("%@complete_quote: %s%@\n", RED, *stack, I);
	}
	// else
		// ft_putendl("complete_quote: QUOTE");
	(*i)++;
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
		// ft_putendl("st_tok: RESET");
		len = 100;
		return ;
	}
	// ft_printf("st_tok: len = %d\n", len);
	if ((i = (int)ft_strlen(*stack)) == (len - 1))
	{
		i = -1;
		if (!(tmp = (char *)malloc(sizeof(char) * (len + 100))))
			exit(0);
		ft_memset(tmp, 0, (len + 100));
		while ((*stack)[++i])
			tmp[i] = (*stack)[i];
		tmp[i] = c;
		// ft_printf("[remaloc]char: %c\n", c);
		ft_strdel(stack);
		*stack = tmp;
		len += 100;
	}
	else
	{
		(*stack)[i] = c;
		// ft_printf("char: %c\n", c);
	}
}
