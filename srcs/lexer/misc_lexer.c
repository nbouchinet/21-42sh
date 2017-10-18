/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 15:30:01 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/18 12:38:44 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	stuck_quote(char **stack, char *line, int *i)
{
	int		j;
	char	*str;
	char	*new;

	j = -1;
	str = NULL;
	if (*stack)
	{
		str = ft_memalloc(100);
		st_tok(NULL, 0, 1);
		complete(&str, line, i);
		st_tok(NULL, 0, 1);
		new = ft_strdup(*stack);
		ft_strdel(stack);
		complete_st_quote(stack, &new, &str);
	}
}

void	complete(char **stack, char *line, int *i)
{
	int		type;
	char	quote;

	quote = '\0';
	if (line[(*i)])
		quote = line[(*i)++];
	type = (quote == '\'' ? QUOTE : DQUOTE);
	in_quote(stack, line, i, quote);
	if (line[(*i)] && !is_space(line[(*i)]) &&
			line[(*i)] != '"' && line[(*i)] != '\'')
		after_quote(stack, line, i);
	if (quote == '"' && line[(*i)] && !is_space(line[(*i)]) &&
				line[(*i)] != '"' && line[(*i)] != '\'')
		expanse_stack(stack, line, i);
	if (line[(*i) + 1] != '\0' && check_end(line + ((*i) + 1)))
		if (line[(*i)] == '\'' || line[(*i)] == '"')
			stuck_quote(stack, line, i);
}

int		print_error_lexer(t_tok **lst, t_tok **n, int mod)
{
	if (mod == 1)
		fd_printf(2, "parse error near unexpected token `%s'\n", (*lst)->str);
	else if (mod == 2)
		write(2, "parse error near unexpected token `newline'\n", 45);
	else if (mod == 3)
		fd_printf(2, "parse error near unexpected token `%s'\n", (*lst)->str);
	else if (mod == 4)
		fd_printf(2, "parse error near unexpected token `%s'\n", (*n)->str);
	return (1);
}

void	replace_tok(t_tok **start, t_tok **next, t_tok **sub, t_tok **sub_end)
{
	t_tok	*start2;
	t_tok	*next2;
	t_tok	*sub2;
	t_tok	*sub_end2;

	start2 = *start;
	next2 = *next;
	sub2 = *sub;
	sub_end2 = *sub_end;
	if (start2 != next2)
		start2->n = *sub;
	if (next2->type != IO_N)
		next2->n->n = sub_end2->n ? sub_end2->n : NULL;
	else
		next2->n->n->n = sub_end2->n ? sub_end2->n : NULL;
	sub_end2->n = next2;
}

void	swap_tok(t_tok **lst, t_tok **start, t_tok **next, t_tok **w)
{
	t_tok	*tmp;

	tmp = *w;
	while (tmp && tmp->n && (tmp->n->type & (WORD | LOCAL)))
		tmp = tmp->n;
	(*lst == *next) ? *lst = *w : 0;
	replace_tok(*start ? start : next, next, w, &tmp);
}
