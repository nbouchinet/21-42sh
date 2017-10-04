/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 18:21:27 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/14 18:21:40 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	get_modifiers(char *event, t_bang *bang)
{
	event[0] == 'h' ? bang->mod |= HB : 0;
	event[0] == 't' ? bang->mod |= TB : 0;
	event[0] == 'r' ? bang->mod |= RB : 0;
	event[0] == 'e' ? bang->mod |= EB : 0;
	event[0] == 'p' ? bang->mod |= PB : 0;
	event[0] == 'q' ? bang->mod |= QB : 0;
	event[0] == 'x' ? bang->mod |= XB : 0;
	if (!ft_strchr("htrepqx", event[0]))
		return (fd_printf(2, "\n42sh: %c: unrecognized history modifier",\
		event[0]));
	return (0);
}

static int	get_designators(char *event, t_bang *bang, int max_arg)
{
	char	**range;
	char	*ptr;

	if (event[0] >= '0' && event[0] <= '9' && !ft_strchr(event, '-') &&
	!ft_strchr(event, '*'))
		bang->des = ft_atoi(event);
	else if (event[0] == '^' || event[0] == '$')
		bang->des = event[0] == '^' ? 1 : max_arg;
	else if ((ptr = ft_strchr(event, '-')))
	{
		range = ft_strsplit(event, '-');
		if ((range[0] && (range[0][0] < '0' || range[0][0] > '9')) || (range[1] &&
		(range[1][0] < '0' || range[1][0] > '9')))
			return (fd_printf(2, "\n42sh: %s%@%@: invalid length specifier",
			range[0], range[1] ? "-" : "", range[1] ? range[1] : ""));
		if (ptr && *(ptr + 1) == 0)
		{
			bang->x = ft_atoi(range[0]);
			bang->y = max_arg - 1;
		}
		else if (ptr && ptr == event)
		{
			bang->x = 0;
			bang->y = ft_atoi(range[0]);
		}
		else
		{
			bang->x = ft_atoi(range[0]);
			bang->y = ft_atoi(range[1]);
		}
		ft_free(range, NULL, 1);
	}
	else if (ft_strchr(event, '*'))
	{
		bang->x = event[0] == '*' ? 0 : ft_atoi(event);
		bang->y = max_arg;
	}
	else
		return (fd_printf(2, "\n42sh: !%s: event not found", event));
	bang->mod |= 128;
	return (0);
}

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

static int	get_event(char *event, t_bang *bang)
{
	char	**qsub;

	if (event[0] >= '0' && event[0] <= '9')
		bang->n = ft_atoi(event);
	else if (event[0] == '-' && event[1] && event[1] >= '0' && event[1] <= '9')
		bang->n = -(ft_atoi(event + 1));
	else if (event[0] == '!')
		bang->n = -1;
	else if (event[0] == '?' && (bang->qm = 1))
		bang->string = event + 1;
	else if (event[0] == '^')
	{
		qsub = ft_strsplit(event, '^');
		bang->s1 = qsub[0] ? ft_strdups(qsub[0], &bang->s1) : NULL;
		bang->s2 = qsub[1] ? ft_strdups(qsub[1], &bang->s2) : NULL;
		ft_free(qsub, NULL, 1);
	}
	else if (ft_isalpha(event[0]))
		bang->string = event;
	else
		return (fd_printf(2, "\n42sh: !%s: event not found", event));
	return (0);
}

static int	bang_error(char *sub, char **opt)
{
	fd_printf(2, "\n42sh: %s: event not found", sub[0] == '^' ? sub : opt[0]);
	ft_free(opt, NULL, 1);
	return (1);
}

int		bang_parse(char *sub, t_bang *bang)
{
	t_his		*his;
	char		**opt;

	opt = ft_strsplit(sub, ':');
	if (!(his = (*his_slg())->n))
		return (bang_error(sub, opt));
	if ((opt && opt[0] && get_event(opt[0], bang)) ||
	(check_ed(bang, his_len(&his), 0)) || (bang->n ? get_line(his, bang) :
	get_match(his, bang)))
		return (ft_free(opt, NULL, 1));
	if (opt && opt[1] && ((opt[1][0] >= '0' && opt[1][0] <= '9') ||
	((opt[1][0] == '^' || opt[1][0] == '$' || opt[1][0] == '*' ||
	opt[1][0] == '-'))) && (get_designators(opt[1], bang,
	ft_nbr_words(bang->tmp, ' ') - 1)))
		return (ft_free(opt, &bang->tmp, 3));
	if ((opt && opt[1] && opt[2] && !ft_isdigit(opt[2][0]) && (opt[2][0] != '^'
	&& opt[2][0] != '$' && opt[2][0] != '*' && opt[2][0] != '-' &&
	get_modifiers(opt[2], bang))) || (opt && opt[1] && !ft_isdigit(opt[1][0]) &&
	(opt[1][0] != '$' && opt[1][0] != '*' && opt[1][0] != '-' && opt[1][0] !=
	'^' && get_modifiers(opt[1], bang))))
		return (ft_free(opt, &bang->tmp, 3));
	if (bang_sub(bang))
		return (ft_free(opt, &sub, 2));
	ft_free(opt, &sub, 3);
	return (0);
}
