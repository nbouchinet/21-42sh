/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jonathan_kent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:40:06 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/04 16:25:54 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	quote(t_tok **lst, char **stack, char *line, int *i)
{
	char	tmp[2];
	char	quote;

	if (ft_strlen(*stack) > 1)
	{
		tok_save(lst, stack, WORD);
		init_token(&(*lst)->next);
		*lst = (*lst)->next;
	}
	if (line[(*i) + 1] && fill_tmp(tmp, line[(*i)++]))
		(*stack) = ft_strdup(tmp);
	quote = (*stack)[0];
	while (line[(*i)] && line[(*i)] != quote && fill_tmp(tmp, line[(*i)++]))
		(*stack) = ft_strjoinf((*stack), tmp, 1);
	fill_tmp(tmp, line[(*i)++]);
	(*stack) = ft_strjoinf((*stack), tmp, 1);
	tok_save(lst, stack, QUOTE);
	if (check_end(line + ((*i) + 1)))
	{
		init_token(&(*lst)->next);
		*lst = (*lst)->next;
	}
}

void	chevron(t_tok **lst, char **stack, char *line, int *i)
{
	int					j;
	static const t_che	key[3] = {{'>'}, {'<'}, {'&'}};

	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, io_number(*stack) ? IO_N : WORD);
		init_token(&(*lst)->next);
		*lst = (*lst)->next;
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
	init_token(&(*lst)->next);
	*lst = (*lst)->next;
}

void	question_mark(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, WORD);
		init_token(&(*lst)->next);
		*lst = (*lst)->next;
	}
	st_tok(stack, line[(*i)]);
	tok_save(lst, stack, QM);
	if (check_end(line + (*i) + 1) == 1)
		{
			init_token(&(*lst)->next);
			*lst = (*lst)->next;
		}
}

void	pipe_pars(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, WORD);
		init_token(&(*lst)->next);
		*lst = (*lst)->next;
	}
	st_tok(stack, line[(*i)]);
	if (line[(*i) + 1] == '|')
	{
		st_tok(stack, line[++(*i)]);
		tok_save(lst, stack, OR);
	}
	else
		tok_save(lst, stack, PIPE);
	init_token(&(*lst)->next);
	*lst = (*lst)->next;
}

void	and_pars(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, WORD);
		init_token(&(*lst)->next);
		*lst = (*lst)->next;
	}
	st_tok(stack, line[(*i)]);
	if (line[(*i) + 1] == '&')
	{
		st_tok(stack, line[++(*i)]);
		tok_save(lst, stack, AND);
	}
	else
		tok_save(lst, stack, -1);
	init_token(&(*lst)->next);
	*lst = (*lst)->next;
}
