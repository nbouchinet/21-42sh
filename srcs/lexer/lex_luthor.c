/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_luthor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 15:14:13 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/24 13:24:29 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		zap_space(char *line)
{
	int		i;

	i = 0;
	while (line[i] && is_space(line[i]) == 1)
		i++;
	return (i);
}

void	init_token(t_tok **lst)
{
	if (!((*lst) = (t_tok*)malloc(sizeof(t_tok))))
		return ;
	(*lst)->type = 0;
	(*lst)->str = NULL;
	(*lst)->next = NULL;
}

void	tok_save(t_tok **lst, char **stack, int type)
{
	int		i;

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
	(*lst)->type = type;
	ft_bzero(*stack, ft_strlen(*stack) + 1);
}

void	flush(t_tok **lst, char **stack, char *line, int *i)
{
	if (ft_strlen(*stack) > 0)
	{
		tok_save(lst, stack, WORD);
		if (check_end(line + (*i)) == 1)
		{
			init_token(&(*lst)->next);
			*lst = (*lst)->next;
		}
	}
	(*i) = (*i) + zap_space(line + (*i)) - 1;
}


void	new_parser(t_tok **cmd, char *line)
{
	int					i;
	int					j;
	char				*stack;
	t_tok				*tmp;
	static const t_key	key[7] = {{'"', &quote}, {' ', &flush}, {'>', &chevron},
{'<', &chevron}, {';', &question_mark}, {'|', &pipe_pars}, {'&', &and_pars}};

	i = 0;
	tmp = *cmd;
	stack = NULL;
	while (line[i])
	{
		j = -1;
		while (++j < 7)
			if (line[i] == key[j].i)
			{
				key[j].f(&tmp, &stack, line, &i);
				break ;
			}
		j == 7 ? st_tok(&stack, line[i]) : 0;
		i++;
	}
	ft_strlen(stack) > 0 ? tok_save(&tmp, &stack, WORD) : 0;
	free(stack);
}
