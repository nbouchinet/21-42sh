/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 18:37:00 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/10 18:32:19 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		qsub_error(t_bang *bang, char **qsub)
{
	fd_printf(2, "\n42sh: ^%s^%s: substitution failed", bang->s1, bang->s2 ?
	bang->s2 : "");
	ft_free(qsub, &bang->tmp, 3);
	ft_strdel(&bang->s1);
	ft_strdel(&bang->s2);
	return (1);
}

static void		quick_sub(t_bang *bang, char **cmd, int len_cmd, int len_sub)
{
	char			**qsub;
	int				j;

	qsub = ft_strsplit(bang->tmp, ' ');
	j = -1;
	ft_memset((*cmd), 0, len_cmd);
	while (qsub[++j] && ft_strcmp(bang->s1, qsub[j]))
		;
	if (!qsub[j] && qsub_error(bang, qsub))
		return ;
	ft_strdel(&qsub[j]);
	qsub[j] = bang->s2;
	j = -1;
	while (qsub[++j])
		len_sub += ft_strlen(qsub[j]);
	while (len_sub > (*cmdl_slg())->line.len)
		remalloc_cmdl(&(*cmdl_slg())->line);
	j = -1;
	while (qsub[++j])
	{
		*cmd = ft_strcat(*cmd, qsub[j]);
		*cmd = ft_strcat(*cmd, qsub[j + 1] ? " " : "\0");
	}
	ft_strdel(&bang->s1);
	ft_free(qsub, NULL, 1);
}

void			fill_buf(t_bang *bang, char **cmd, int *i)
{
	char			*sub;
	int				len_cmd;
	int				len_sub;

	len_cmd = ft_strlen(*cmd);
	if (bang->s1)
	{
		quick_sub(bang, cmd, len_cmd, 0);
		*i = ft_strlen(*cmd);
		return ;
	}
	sub = ft_strdup(*cmd + bang->end);
	len_sub = ft_strlen(bang->tmp);
	ft_memset(*cmd + bang->start, 0, len_cmd + bang->start);
	while (len_cmd - (bang->end - bang->start) + len_sub >
	(*cmdl_slg())->line.len)
		remalloc_cmdl(&(*cmdl_slg())->line);
	*cmd = ft_strcat(*cmd, bang->tmp);
	*i = ft_strlen(*cmd) - 1;
	*cmd = ft_strcat(*cmd, sub);
	ft_strdel(&sub);
	ft_strdel(&bang->tmp);
}

static char		*get_bang(int *i, char *cmd, t_bang *bang)
{
	int		start;
	int		end;

	start = 0;
	end = 0;
	ft_memset(bang, 0, sizeof(t_bang));
	bang->x = -1;
	bang->y = -1;
	bang->des = -1;
	bang->start = *i;
	start = cmd[*i] == '!' ? *i + 1 : *i;
	(*i) += cmd[*i + 1] == '!' ? 1 : 0;
	while (cmd[++(*i)] && cmd[(*i)] != '<' && cmd[(*i)] != '>' &&
	cmd[(*i)] != '"' && cmd[(*i)] != '\'' && cmd[(*i)] != ';' &&
	cmd[(*i)] != '|' && cmd[(*i)] != '&' && cmd[(*i)] != '!' && cmd[(*i)] != '*'
	&& cmd[(*i)] != '$' && cmd[(*i)] != ' ')
		;
	end = *i;
	bang->end = *i;
	*i -= 1;
	return (ft_strsub(cmd, start, end - start));
}

int				bang(char *cmd)
{
	int		i;
	int		ret;
	t_bang	bang;

	i = -1;
	ret = 0;
	while (cmd[++i])
		if ((cmd[i] == '!' || (cmd[i] == '^' && i == 0)) && cmd[i + 1] != ' ' &&
		cmd[i + 1] != '\t' && cmd[i + 1] != '=' && cmd[i + 1] != '\0')
		{
			if ((ret = bang_parse(get_bang(&i, cmd, &bang), &bang)))
			{
				ft_memset((*cmdl_slg())->line.str, 0,
				ft_strlen((*cmdl_slg())->line.str));
				return (1);
			}
			else
				fill_buf(&bang, &(*cmdl_slg())->line.str, &i);
		}
	return (0);
}
