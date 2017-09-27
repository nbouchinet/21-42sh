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

static int	get_designators(char *event, t_bang *bang)
{
	char	**range;
	char	*ptr;

	if (event[0] >= '0' && event[0] <= '9' && !ft_strchr(event, '-') &&
	!ft_strchr(event, '*'))
		bang->des = ft_atoi(event);
	else if (event[0] == '^' || event[0] == '$')
		bang->des = event[0] == '^' ? 1 : -1;
	else if ((ptr = ft_strchr(event, '-')))
	{
		range = ft_strsplit(event, '-');
		if (ptr && *(ptr + 1) == 0)
		{
			bang->x = ft_atoi(range[0]);
			bang->y = -2;
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
		bang->x = event[0] == '*' ? 1 : ft_atoi(event);
		bang->y = -1;
	}
	else
		return (fd_printf(2, "\n42sh: !%s: event not found", event));
	bang->mod |= 128;
	return (0);
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
	ft_free(opt, &sub, 1);
	return (1);
}

int			bang_parse(char *sub, t_bang *bang)
{
	t_his	*his;
	char	**opt;
	int		len;

	opt = ft_strsplit(sub, ':');
	len = ft_tablen(opt);
	if (!(his = (*his_slg())))
		return (bang_error(sub, opt));
	if (0 < len && get_event(opt[0], bang))
		return (ft_free(opt, NULL, 1));
	if (1 < len && ((opt[1][0] >= '0' && opt[1][0] <= '9') || (opt[1][0] == '^'
	|| opt[1][0] == '$' || opt[1][0] == '*' || opt[1][0] == '-'))
	&& get_designators(opt[1], bang))
		return (ft_free(opt, &sub, 3));
	if ((2 < len && !ft_isdigit(opt[2][0]) && (opt[2][0] != '^' &&
	opt[2][0] != '$' && opt[2][0] != '*' && opt[2][0] != '-' &&
	get_modifiers(opt[2], bang))) || (1 < len && !ft_isdigit(opt[1][0]) &&
	(opt[1][0] != '$' && opt[1][0] != '*' && opt[1][0] != '-' &&
	opt[1][0] != '^' && get_modifiers(opt[1], bang))))
		return (ft_free(opt, &sub, 3));
	if (bang_sub(bang, his))
		return (ft_free(opt, &sub, 2));
	ft_free(opt, &sub, 3);
	return (0);
}
