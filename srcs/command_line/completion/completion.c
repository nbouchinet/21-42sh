/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:23:17 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/30 17:32:34 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void			display_list(t_ls *list, char **cmd, char *path, t_win **win)
{
	char		*save;

	save = ft_strdup((*cmd) + ((*win)->cur - (*win)->pr));
	OR_SEP ? arrow_left(*win, NULL, NULL) : 0;
	while (SEP && (*win)->cur - (*win)->pr)
		arrow_left(*win, NULL, NULL);
	(*cmd)[(*win)->cur - (*win)->pr +
	((*win)->cur - (*win)->pr ? 1 : 0)] = 0;
	(*cmd) = path[0] == '.' && path[1] != '.' ?
	ft_strjoinf((*cmd), path + 1, 1) : ft_strjoinf((*cmd), path, 1);
	(*cmd) = ft_strjoinf((*cmd), (list)->name, 1);
	(*cmd) = ft_strjoinf((*cmd), save, 3);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	write(1, (*cmd) + ((*win)->cur - (*win)->pr),
			ft_strlen((*cmd) + ((*win)->cur - (*win)->pr)));
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	arrow_rigth(*win, *cmd, NULL);
	while (SEP && (*cmd)[(*win)->cur - (*win)->pr])
		arrow_rigth(*win, *cmd, NULL);
}

int				call_print_lst(t_win **win, char **cmd, t_ls *list, int i)
{
	if (i)
	{
		end(*win, NULL, NULL);
		write(1, "\n", 1);
		print_lst(&list, win, (*cmd), 0);
		list_del(&list);
		return (1);
	}
	else
	{
		end(*win, NULL, NULL);
		write(1, "\n", 1);
		print_lst(&list, win, (*cmd), 0);
		list_del(&list);
	}
	return (0);
}

static int		only_space(char *cmd, t_win *win)
{
	int			i;

	if (!cmd)
	{
		write(1, "\033[1mRTFM\n", 9);
		print_prompt(&win);
		return (1);
	}
	i = -1;
	while (cmd[++i])
		if (cmd[i] != ' ' && cmd[i] != 0)
			return (0);
	home(win, NULL, NULL);
	write(1, "\033[1mRTFM\n", 9);
	print_prompt(&win);
	return (1);
}

static void		get_comp(t_win **win, char **cmd, int i, char *tmp)
{
	if (i - 1 < 0 || (*cmd)[i - 1] == '|' || (*cmd)[i - 1] == ';'
	|| (*cmd)[i - 1] == '&' || (*cmd)[i - 1] == '<' || (*cmd)[i - 1] == '>')
		return ;
	while (--i > 0 && (*cmd)[i] != ' ' && (*cmd)[i] != '|' && (*cmd)[i] != ';'
	&& (*cmd)[i] != '&' && (*cmd)[i] != '<' && (*cmd)[i] != '>')
		;
	i += (i < 0 ? 1 : 0);
	while ((*cmd)[(*win)->cur - (*win)->pr] && SEP)
		arrow_rigth((*win), (*cmd), NULL);
	if ((*cmd)[(*win)->cur - (*win)->pr - 1] != ' ')
		tmp = ft_strsub((*cmd), (i ? i + 1 : i),
		(*win)->cur - (*win)->pr - i - (i ? 1 : 0));
	else
		tmp = NULL;
	(*win)->tmp = i;
	if (tmp && is_first_word((*cmd), (*win)->cur - (*win)->pr))
		list_exe(tmp, ft_strsplit(lst_at(&(*win)->lstenv, "PATH")->value, ':'),
		win, cmd) ? 0 : (list_files(&tmp, win, cmd));
	else
		list_files(&tmp, win, cmd);
	tmp ? free(tmp) : 0;
}

void			completion(t_win **win, char **cmd)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = (*win)->cur - (*win)->pr;
	if (!(*win)->hd && !(*win)->quote)
		if ((!((*win)->lstenv)) || (!(lst_at(&(*win)->lstenv, "PATH")))
		|| only_space(*cmd, *win))
			return ;
	get_comp(win, cmd, i, tmp);
}
