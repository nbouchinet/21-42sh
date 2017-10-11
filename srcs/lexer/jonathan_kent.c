/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jonathan_kent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:40:06 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/11 10:43:06 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	quote(t_tok **lst, char **stack, char *line, int *i)
{
	int		type;
	char	quote;

	quote = line[(*i)++];
	if (ft_strlen(*stack) > 0)
		type = WORD;
	else
		type = (quote == '\'' ? QUOTE : DQUOTE);
	while (line[(*i)] && line[(*i)] != quote)
	{
		if (quote == '"' && line[(*i)] == '\\')
			st_tok(stack, line[++(*i)], 0);
		else
			st_tok(stack, line[(*i)++], 0);
	}
	tok_save(lst, stack, type);
	if (line[(*i) + 1] != '\0' && check_end(line + ((*i) + 1)))
	{
		(*lst)->n = init_tok(lst, NE);
		*lst = (*lst)->n;
	}
}

void	chevron(t_tok **lst, char **stack, char *line, int *i)
{
	int					j;
	static const t_che	key[3] = {{'>'}, {'<'}, {'&'}};

	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, io_number(*stack) ? IO_N : WORD);
		(*lst)->n = init_tok(lst, NE);
		*lst = (*lst)->n;
	}
	st_tok(stack, line[(*i)++], 0);
	j = -1;
	while (++j < 3)
		if (line[(*i)] == key[j].c &&
			((*stack)[0] == key[j].c || line[(*i)] == '&'))
		{
			st_tok(stack, line[(*i)], 0);
			break ;
		}
	j == 3 ? (*i)-- : (*i);
	tok_save(lst, stack, CHEVRON);
	if (line[(*i) + 1] != '\0' && check_end(line + ((*i) + 1)))
	{
		(*lst)->n = init_tok(lst, NE);
		*lst = (*lst)->n;
	}
}

void	question_mark(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, WORD);
		(*lst)->n = init_tok(lst, NE);
		*lst = (*lst)->n;
	}
	st_tok(stack, line[(*i)], 0);
	tok_save(lst, stack, QM);
	if (check_end(line + (*i) + 1) == 1)
	{
		(*lst)->n = init_tok(lst, NE);
		*lst = (*lst)->n;
	}
}

void	pipe_pars(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, WORD);
		(*lst)->n = init_tok(lst, NE);
		*lst = (*lst)->n;
	}
	st_tok(stack, line[(*i)], 0);
	if (line[(*i) + 1] == '|')
	{
		st_tok(stack, line[++(*i)], 0);
		tok_save(lst, stack, OR);
	}
	else
		tok_save(lst, stack, PIPE);
	(*lst)->n = init_tok(lst, NE);
	*lst = (*lst)->n;
}

void	and_pars(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, WORD);
		(*lst)->n = init_tok(lst, NE);
		*lst = (*lst)->n;
	}
	st_tok(stack, line[(*i)], 0);
	if (line[(*i) + 1] == '&')
	{
		st_tok(stack, line[++(*i)], 0);
		tok_save(lst, stack, AND);
	}
	else
		tok_save(lst, stack, BG);
	if (check_end(line + (*i) + 1) == 1)
	{
		(*lst)->n = init_tok(lst, NE);
		*lst = (*lst)->n;
	}
}
