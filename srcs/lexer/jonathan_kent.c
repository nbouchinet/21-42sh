/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jonathan_kent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:40:06 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/09 18:48:10 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	quote(t_tok **lst, char **stack, char *line, int *i)
{
	char	quote;

	quote = line[(*i)++];
	while (line[(*i)] && line[(*i)] != quote)
		st_tok(stack, line[(*i)++]);
	tok_save(lst, stack, WORD);
	if (line[(*i) + 1] != '\0' && check_end(line + ((*i) + 1)))
	{
		init_token(&(*lst)->n);
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
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
	st_tok(stack, line[(*i)++]);
	j = -1;
	while (++j < 3)
		if (line[(*i)] == key[j].c &&
			((*stack)[0] == key[j].c || line[(*i)] == '&'))
		{
			st_tok(stack, line[(*i)]);
			break ;
		}
	j == 3 ? (*i)-- : (*i);
	tok_save(lst, stack, CHEVRON);
	if (line[(*i) + 1] != '\0' && check_end(line + ((*i) + 1)))
	{
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
}

void	question_mark(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, WORD);
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
	st_tok(stack, line[(*i)]);
	tok_save(lst, stack, QM);
	if (check_end(line + (*i) + 1) == 1)
		{
			init_token(&(*lst)->n);
			*lst = (*lst)->n;
		}
}

void	pipe_pars(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, WORD);
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
	st_tok(stack, line[(*i)]);
	if (line[(*i) + 1] == '|')
	{
		st_tok(stack, line[++(*i)]);
		tok_save(lst, stack, OR);
	}
	else
		tok_save(lst, stack, PIPE);
	init_token(&(*lst)->n);
	*lst = (*lst)->n;
}

void	and_pars(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, WORD);
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
	st_tok(stack, line[(*i)]);
	if (line[(*i) + 1] == '&')
	{
		st_tok(stack, line[++(*i)]);
		tok_save(lst, stack, AND);
	}
	else
		tok_save(lst, stack, BG);
	if (check_end(line + (*i) + 1) == 1)
	{
		init_token(&(*lst)->n);
		*lst = (*lst)->n;
	}
}
