/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 17:42:31 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/30 17:51:24 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int      mod_cmd(char **cmd, char **array, t_bang *bang)
{
  int     ret;
  char    *beg;
  char    *end;

  (*cmd)[bang->b] = 0;
  beg = ft_strdup(*cmd);
  end = ft_strdup(*cmd + bang->e);
  ft_printf("\n%%s\n%s\n", beg, end);
  ret = -1;
  while (array[++ret])
    if (!ft_strcmp(array[ret], bang->s1))
    {
      ft_strdel(&array[ret]);
      array[ret] = ft_strdup(bang->s2);
      break ;
    }
  if (!array[ret])
    return (fd_printf(2, "\n42sh: substituion failed\n"));
  ft_strdel(cmd);
  ret = -1;
  beg ? (*cmd) = ft_strdup(beg) : 0;
  while (array[++ret])
    (*cmd) = ft_strjoinf(ft_strjoinf(*cmd, array[ret], 0), " ", 1);
  (*cmd) = ft_strjoinf((*cmd), end, 3);
  return (2);
}

void 				fill_buf(char *tmp, char **cmd, int i, int j)
{
	static char	*buf = NULL;
	char				*sub;
	int					b;
	int					e;

	if (j)
	{
		ft_strdel(cmd);
		*cmd = ft_strdupf(&buf);
		return ;
	}
	!buf ? buf = ft_strdup(*cmd) : 0;
	while (buf[++i])
		if (buf[i] == '!')
		{
			b = i ;
			buf[i + 1] == '!' ? i += 1 : 0;
			while (buf[++i] && buf[i] != '<' && buf[i] != '>' && buf[i] != '\"' &&
			buf[i] != '\'' && buf[i] != ';' && buf[i] != '|' && buf[i] != '&' &&
			buf[i] != '!')
				;
			e = i;
			sub = ft_strdup(buf + e);
			buf[b] = 0;
			buf = ft_strjoinf(ft_strjoinf(ft_strjoinf(buf, tmp, 1), " ", 1), sub, 3);
			break ;
		}
}

static int 	is_bang(char **cmd, int i, int b, int e)
{
	int			k;
	int			ret;
	t_bang	bang;

	k = 0;
	while ((*cmd)[++i])
		if (((*cmd)[i] == '!' || (*cmd)[i] == '^') && ((*cmd)[i + 1] != ' ' &&
		(*cmd)[i + 1] != '\t' && (*cmd)[i + 1] != '=' && (*cmd)[i + 1] != '\0'))
		{
			k = 1;
			ft_memset(&bang, 0, sizeof(bang));
			b = (*cmd)[i] == '!' ? i + 1 : i;
			(*cmd)[i + 1] == '!' ? i += 1 : 0;
			while ((*cmd)[++i] && (*cmd)[i] != '<' && (*cmd)[i] != '>' &&
			(*cmd)[i] != '\"' && (*cmd)[i] != '\'' && (*cmd)[i] != ';' &&
			(*cmd)[i] != '|' && (*cmd)[i] != '&' && (*cmd)[i] != '!')
				;
			e = i;
			bang.b = b;
			bang.e = e;
			i -= 1;
			if ((ret = bang_bang(cmd, ft_strsub(*cmd, b, e - b), &bang)))
			{
				if (ret == 2)
					return (0);
				ft_strdel(cmd);
				return (1);
			}
		}
	k ? fill_buf(NULL, cmd, 0, 1) : 0;
	return (0);
}

static void		first_link(t_win *win, char **cmd, t_his **his)
{
	t_his	*tmp;

	if (!(tmp = (t_his *)malloc(sizeof(t_his))))
		exit (fd_printf(2, "malloc error\n"));
	tmp->cmdl = ft_strdup(*cmd);
	tmp->len = ft_strlen((*cmd)) + 1;
	tmp->prev = NULL;
	tmp->next = (*his);
	(*his)->prev = tmp;
	win->hd ? catcmd(win, cmd) : 0;
	ft_streplace(&(*his)->cmdl, 127, '\n');
}

void			save_history(t_win *win, char **cmd, t_his **his)
{
	t_his	*tmp;

	if (!(*cmd) || !(*cmd)[0] || is_bang(cmd, -1, -1, -1))
		return ;
	if (!(*his)->next && !(*his)->prev)
	{
		first_link(win, cmd, his);
		return ;
	}
	while ((*his)->next)
		(*his) = (*his)->next;
	tmp = (*his);
	(*his) = (*his)->prev;
	if (!((*his)->next = (t_his *)malloc(sizeof(t_his))))
		exit(fd_printf(2, "save-hisroty: malloc error\n"));
	(*his)->next->cmdl = ft_strdup((*cmd));
	(*his)->next->prev = (*his);
	(*his)->next->next = tmp;
	(*his) = (*his)->next;
	(*his)->next->prev = (*his);
	(*his) = (*his)->next;
	ft_streplace(&(*his)->cmdl, 127, ' ');
	win->hd ? catcmd(win, cmd) : 0;
}
