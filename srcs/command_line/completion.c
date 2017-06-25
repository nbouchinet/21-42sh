/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:23:17 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/29 15:23:20 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			call_print_lst(t_win **win, char **cmd, t_ls *list, int i)
{
	char			buf[3];
	
	buf[0] = 27;
	buf[1] = 91;
	buf[2] = 70;
	if (i)
	{
		arrows((*win), (*cmd), buf);
		write(1, "\n", 1);
		print_lst(&list, win, (*cmd), 0);
		list_del(&list);
		return (1);
	}
	else
	{
		arrows((*win), (*cmd), buf);
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
	while (win->cur > win->pr)
		arrow_left(win);
	write(1, "\033[1mRTFM\n", 9);
	print_prompt(&win);
	return (1);
}

void    		completion(t_win **win, char **cmd)
{
	int     i;
	char    *tmp;

	tmp = NULL;
	if (!(*win)->hd && !(*win)->quote)
		if ((!((*win)->lstenv)) || (!(lst_at(&(*win)->lstenv, "PATH")))
		|| only_space(*cmd, *win))
			return ;
	i = (*win)->cur - (*win)->pr;
	if (i - 1 < 0 || (*cmd)[i - 1] == '|' || (*cmd)[i - 1] == ';' 
	|| (*cmd)[i - 1] == '&' || (*cmd)[i - 1] == '<' || (*cmd)[i - 1] == '>')
		return ;
	while (--i > 0 && (*cmd)[i] != ' ' && (*cmd)[i] != '|' && (*cmd)[i] != ';'
	&& (*cmd)[i] != '&' && (*cmd)[i] != '<' && (*cmd)[i] != '>')
		;
	i += (i < 0 ? 1 : 0); 
	while ((*cmd)[(*win)->cur - (*win)->pr] && SEP)
		arrow_rigth((*win), (*cmd));
	tmp = (*cmd)[(*win)->cur - (*win)->pr - 1] == ' ' ? NULL : 
	ft_strsub((*cmd), (i ? i + 1 : i), (*win)->cur - (*win)->pr - i - (i ? 1 : 0));
	if (tmp && is_first_word((*cmd), (*win)->cur - (*win)->pr))
		list_exe(tmp, ft_strsplit(lst_at(&(*win)->lstenv, "PATH")->value, ':'),
		win, cmd, i) ? 0 : (list_files(&tmp, win, cmd));
	else
		list_files(&tmp, win, cmd);
	tmp ? free(tmp) : 0;
}
