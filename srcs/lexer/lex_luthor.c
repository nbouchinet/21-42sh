/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_luthor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 15:14:13 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/30 19:15:25 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_token(t_tok **lst)
{
	if (!((*lst) = (t_tok*)malloc(sizeof(t_tok))))
		return ;
	(*lst)->type = 0;
	(*lst)->str = NULL;
	(*lst)->n = NULL;
}

void	tok_save(t_tok **lst, char **stack, int type)
{
	int		i;
	char	*bs;

	i = ft_strlen(*stack);
	if (!((*lst)->str = (char*)malloc(sizeof(char) * (i + 1))))
		return ;
	i = 0;
	while ((*stack)[i])
	{
		(*lst)->str[i] = (*stack)[i];
		i++;
	}
	(*lst)->str[i] = '\0';
	if (type == WORD && ft_isalpha((*lst)->str[0]) && ft_strchr((*lst)->str, '='))
		(*lst)->type = LOCAL;
	else
		(*lst)->type = type;
	if ((*lst)->type != QUOTE && (bs = ft_strchr((*lst)->str, '\\')) &&
	*(bs + 1) != '*' && *(bs + 1) != '$' && *(bs + 1) != ';' &&
	*(bs + 1) != '<' && *(bs + 1) != '>' && *(bs + 1) != ' ' && *(bs + 1) != '\\')
		ft_strleft(&(*lst)->str, '\\');
	ft_memset(*stack, 0, ft_strlen(*stack));
}

void	flush(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, WORD);
		if (check_end(line + (*i)) == 1)
		{
			init_token(&(*lst)->n);
			*lst = (*lst)->n;
		}
	}
	while (line[(*i)] && line[(*i)] == ' ')
		(*i)++;
	(*i)--;
}


void	new_parser(t_tok **cmd, char *line)
{
	int					i;
	int					j;
	char				*stack;
	t_tok				*tmp;
	static const t_key	key[8] = {{'"', &quote}, {'\'', &quote}, {' ', &flush}, {'>', &chevron},
	{'<', &chevron}, {';', &question_mark}, {'|', &pipe_pars}, {'&', &and_pars}};

	i = 0;
	tmp = *cmd;
	stack = ft_memalloc(100);
	while (line[i])
	{
		j = -1;
		while (++j < 8)
			if (line[i] == key[j].i)
			{
				key[j].f(&tmp, &stack, line, &i);
				break ;
			}
		j == 8 ? st_tok(&stack, line[i]) : 0;
		i++;
	}
	stack && ft_strlen(stack) > 0 ? tok_save(&tmp, &stack, WORD) : 0;
	stack ? free(stack) : 0;
}
