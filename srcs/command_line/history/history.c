/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 17:42:31 by khabbar           #+#    #+#             */
/*   Updated: 2017/08/04 14:39:39 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		move_history(t_his **his, char **cmd, char buf, t_win *win)
{
	char		*tmp;

	tmp = (*cmd);
	win->cpy_b = -1;
	win->cpy_e = -1;
	if ((buf == 65 && !(*his)->prev) || (buf == 66 && !(*his)->next))
		return ;
	while (win->cur > win->pr)
		arrow_left(win, NULL, NULL);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	del_all(*cmd, win);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	get_history(his, tmp, cmd, buf);
	win->cur += (int)ft_strlen(*cmd);
}

static void get_bang(int *i, int *b, t_bang *bang, char **cmd)
{
  ft_memset(bang, 0, sizeof(bang));
  bang->des = -5;
  (*b) = (*cmd)[(*i)] == '!' ? (*i) + 1 : (*i);
  (*cmd)[(*i) + 1] == '!' ? (*i) += 1 : 0;
  while ((*cmd)[++(*i)] && (*cmd)[(*i)] != '<' && (*cmd)[(*i)] != '>' &&
  (*cmd)[(*i)] != '\"' && (*cmd)[(*i)] != '\'' && (*cmd)[(*i)] != ';' &&
  (*cmd)[(*i)] != '|' && (*cmd)[(*i)] != '&' && (*cmd)[(*i)] != '!')
    ;
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
      		get_bang(&i, &b, &bang, cmd);
			e = i;
			bang.b = b;
			bang.e = e;
			i -= 1;
			if ((ret = bang_bang(cmd, ft_strsub(*cmd, b, e - b), &bang, 0)))
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
	ft_streplace(&tmp->cmdl, 127, ' ');
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
	(*his)->next->len = ft_strlen((*cmd)) + 1;
	(*his)->next->prev = (*his);
	(*his)->next->next = tmp;
	(*his) = (*his)->next;
	(*his)->next->prev = (*his);
	(*his) = (*his)->next;
	ft_streplace(&(*his)->cmdl, 127, ' ');
	win->hd ? catcmd(win, cmd) : 0;
}
