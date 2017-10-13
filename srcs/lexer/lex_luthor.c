/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_luthor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 15:14:13 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/12 22:32:24 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_token(t_tok **lst)
{
	if (!((*lst) = (t_tok*)malloc(sizeof(t_tok))))
		exit(0);
	(*lst)->type = 0;
	(*lst)->str = NULL;
	(*lst)->hd = 0;
	(*lst)->n = NULL;
}

t_tok	*init_tok(t_tok **lst, int mod)
{
	t_tok	*tmp;

	mod = 0;
	(void)lst;
	if (!(tmp = (t_tok*)malloc(sizeof(t_tok))))
		return (NULL);
	tmp->type = 0;
	tmp->hd = 0;
	tmp->str = NULL;
	tmp->n = NULL;
	return (tmp);
}

void	tok_save(t_tok **lst, char **stack, int type)
{
	if (type & (WORD | DQUOTE))
		stack_expanse(stack);
	(*lst)->str = ft_strdup(*stack);
	if (type == WORD && ft_isalpha((*lst)->str[0]) &&
			ft_strchr((*lst)->str, '='))
		(*lst)->type = LOCAL;
	else
		(*lst)->type = type;
	ft_memset(*stack, '\0', ft_strlen(*stack));
}

void	flush(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		// find_env_loc(stack, 1);
		tok_save(lst, stack, WORD);
		if (check_end(line + (*i)))
		{
			init_token(&(*lst)->n);
			*lst = (*lst)->n;
		}
	}
	while (line[(*i)] && is_space(line[(*i)]))
		(*i)++;
	(*i)--;
}

void	new_parser(t_tok **cmd, char *line, int i)
{
	int					j;
	char				*stack;
	t_tok				*tmp;
	static const t_key	key[9] = {{'"', &ft_quote}, {'\'', &ft_quote},
{' ', &flush}, {'>', &chevron}, {'<', &chevron}, {';', &question_mark},
{'|', &pipe_pars}, {'&', &and_pars}, {'\\', &backslash}};

	tmp = *cmd;
	// ft_putendl(line);
	stack = ft_memalloc(100);
	while (line[i])
	{
		j = -1;
		while (++j < 9)
			if (line[i] == key[j].i)
			{
				// ft_putendl("Salute");
				key[j].f(&tmp, &stack, line, &i);
				break ;
			}
		// ft_putchar(line[i]);
		j == 9 ? st_tok(&stack, line[i], 0) : 0;
		i++;
	}
	stack && ft_strlen(stack) > 0 ? tok_save(&tmp, &stack, WORD) : 0;
	ft_strdel(&stack);
	st_tok(NULL, 0, 1);
}
