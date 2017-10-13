/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 15:30:01 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/13 22:33:21 by zadrien          ###   ########.fr       */
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
		// ft_putendl("IN stuck_quote");
		str = ft_memalloc(100);
		st_tok(NULL, 0, 1);
		if (line[(*i)] == '\'' || line[(*i)] == '"')
		{ // USELESS
			complete(&str, line, i);
			st_tok(NULL, 0, 1);
			new = ft_strdup(*stack);
			ft_strdel(stack);
			// ft_printf("NEW: %@%s%@\n", GREEN, new, I);
			if (!(*stack = (char *)malloc(sizeof(char) * 100)))
				perror("malloc:"); // TO REMOVE
			ft_memset(*stack, 0, 100);
			// ft_putnbrl(j);
			while (new[++j])
			{
				// ft_putchar(new[j]);ft_putchar('\n');
				st_tok(stack, new[j], 0);
			}
			// ft_putendl("BONJOUR");
			ft_strdel(&new);
			// }
			// else perror("malloc stack");
			j = -1;
			if (str)
			{
				// ft_putendl("HELLO");
				while (str[++j])
				{
					// ft_printf("^^^^^^[%c]^^^^^^", str[j]);
					st_tok(stack, str[j], 0);
				}
				ft_strdel(&str);
			}
			// else
				// ft_putendl("NULL");
			// ft_putendl("WORLD");
		}
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
	complete_quote(stack, line, i, quote);
	// ft_putendl("INNER_QUOTE");
	while (line[(*i)] && !is_space(line[(*i)]) && line[(*i)] != '"' && line[(*i)] != '\'')
	{
		if (quote == '"' && line[(*i)] == '\\')
		{
			st_tok(stack, line[++(*i)], 0);
			line[(*i) + 1] ? (*i)++ : 0;
		}
		else
			st_tok(stack, line[(*i)++], 0);
	}
	if (line[(*i) + 1] != '\0' && check_end(line + ((*i) + 1)))
	{
		if (line[(*i)] == '\'' || line[(*i)] == '"')
			stuck_quote(stack, line, i);
		// ft_printf("END INNER_QUOTE: %s\n", *stack);
		// (*i)--;
	}
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
