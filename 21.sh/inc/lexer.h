/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 12:36:43 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/20 12:36:45 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#define	COM		1
#define	OPT		2
#define	COMSEP	3
#define	ROUT	4
#define AROUT	5
#define RINP	6
#define HD		7
#define PIPE	8
#define FD		9
#define	AND		10
#define	OR		11

# define ET		cmdl[i] == '|' && cmdl[i + 1] == '|'
# define OU		cmdl[i] == '&' && cmdl[i + 1] == '&'
# define META	cmdl[i] == '<' || cmdl[i] == '&' || cmdl[i] == '>' || cmdl[i] == ';' || (ET) || (OU)

typedef struct			s_lex
{
	char				*lexeme;
	int					type;
	struct s_lex		*next;
}						t_lex;



void		lexer(t_lex **head, char *cmdl, char **env);
void		del_lex(t_lex **head);

#endif