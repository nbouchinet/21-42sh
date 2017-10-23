/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_parse2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 18:54:26 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 18:57:15 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		ft_nbr_words(char const *s, char c)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	if (s[i] == c || s[i] == '\t')
		i++;
	while (s[i])
	{
		if (s[i] == c || s[i] == '\t')
			if (s[i - 1] != c && s[i - 1] != '\t')
				nbr++;
		i++;
		if (s[i] == '\0')
			if (s[i - 1] != c && s[i - 1] != '\t')
				nbr++;
	}
	return (nbr);
}

int				call_get_modifiers(t_bang *bang, char **opt, char **sub)
{
	if (opt && opt[1] && opt[2] && !ft_isdigit(opt[2][0]) && opt[2][0] != '^'
	&& opt[2][0] != '$' && opt[2][0] != '*' && opt[2][0] != '-' &&
	get_modifiers(opt[2], bang))
	{
		ft_strdel(sub);
		return (ft_free(opt, &bang->tmp, 3));
	}
	if (opt && opt[1] && !ft_isdigit(opt[1][0]) && opt[1][0] != '$' &&
	opt[1][0] != '*' && opt[1][0] != '-' && opt[1][0] != '^' &&
	get_modifiers(opt[1], bang))
	{
		ft_strdel(sub);
		return (ft_free(opt, &bang->tmp, 3));
	}
	return (0);
}

int				call_get_designators(t_bang *bang, t_his *his, char **opt,
				char **sub)
{
	if (opt && opt[1] && ((opt[1][0] >= '0' && opt[1][0] <= '9') ||
	((opt[1][0] == '^' || opt[1][0] == '$' || opt[1][0] == '*' || opt[1][0] ==
	'-'))) && (get_designators(opt[1], bang, ft_nbr_words(bang->tmp, ' ') - 1)))
	{
		ft_strdel(sub);
		return (ft_free(opt, &bang->tmp, 3));
	}
	if (check_ed(bang, his_len(&his), ft_nbr_words(bang->tmp, ' ') - 1, 1))
	{
		ft_strdel(sub);
		return (ft_free(opt, &bang->tmp, 3));
	}
	return (0);
}

int				call_get_event(t_bang *bang, t_his *his, char **opt, char **sub)
{
	if (opt && opt[0] && get_event(opt[0], bang))
	{
		ft_strdel(sub);
		return (ft_free(opt, NULL, 1));
	}
	if (bang->n ? get_line(his, bang) : get_match(his, bang))
	{
		ft_strdel(sub);
		return (ft_free(opt, NULL, 1));
	}
	if (check_ed(bang, his_len(&his), ft_nbr_words(bang->tmp, ' ') - 1, 0))
	{
		ft_strdel(sub);
		return (ft_free(opt, &bang->tmp, 3));
	}
	return (0);
}
