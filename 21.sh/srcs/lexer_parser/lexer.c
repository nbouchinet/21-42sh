/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 17:44:10 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/19 17:44:12 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		del_lex(t_lex **head)
{
	t_lex	*tmp;
	t_lex	*save;

	tmp = *head;
	while (tmp)
	{
		save = tmp->next;
		free(tmp->lexeme);
		free(tmp);
		tmp = save;
	}
}

static int	def_type(char *cmdl, int b)
{
	if (b != 0 && cmdl[0] == '-' && cmdl[1] != 0)
		return (OPT);
	else if (cmdl[0] == '<' && cmdl[1] == '<' && cmdl[2] == 0)
		return (HD);
	else if (cmdl[0] == '<' && cmdl[1] == 0)
		return (RINP);
	else if (cmdl[0] == '>' && cmdl[1] == 0)
		return (ROUT);
	else if (cmdl[0] == '>' && cmdl[1] == '>' && cmdl[2] == 0)
		return (AROUT);
	else if (cmdl[0] == ';' && cmdl[1] == 0)
		return (COMSEP);
	else if (cmdl[0] == '|' && cmdl[1] == 0)
		return (PIPE);
	else if (cmdl[0] == '|' && cmdl[1] == '|' && cmdl[2] == 0)
		return (AND);
	else if (cmdl[0] == '&' && cmdl[1] == '&' && cmdl[2] == 0)
		return (OR);
	else
		return (COM);
}

static t_lex *get_lexeme(t_lex **head, char *cmdl, int b, int e)
{
	t_lex	*tmp;

	tmp = *head;
	if (!tmp)
	{
		if (!(tmp = (t_lex *)malloc(sizeof(t_lex))))
			exit(fd_printf(2, "malloc error\n"));
		tmp->lexeme = ft_strsub(cmdl, b, e == b ? 1 : e - b);
		tmp->type = def_type(tmp->lexeme, b);
		tmp->next = NULL;
		return (tmp);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_lex *)malloc(sizeof(t_lex))))
			exit(fd_printf(2, "malloc error\n"));
		tmp->next->lexeme = ft_strsub(cmdl, b, e == b ? 1 : e - b);
		tmp->next->type = def_type(tmp->next->lexeme, b);
		tmp->next->next = NULL;
		return (tmp->next);
	}
}

void        lexer(t_lex **head, char *cmdl, char **env)
{
	int		i;
	int		b;
	int		e;
	t_lex	*tmp;

	(void)env;
	i = 0;
	while (cmdl[i])
	{
		while (cmdl[i] && cmdl[i] == ' ')
			i += 1;
		b = i;
		if (cmdl[i])
			while (cmdl[i] && cmdl[i] != ' ')
				i += 1;
		e = i;
		!(*head) ? (*head) = get_lexeme(head, cmdl, b, e) : get_lexeme(head, cmdl, b, e);
	}
	tmp = (*head);
	while (tmp)
	{
		ft_putendl(tmp->lexeme);
		ft_putnbrl(tmp->type);
		tmp = tmp->next;
	}
}