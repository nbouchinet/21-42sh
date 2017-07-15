/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 13:37:45 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/15 13:37:53 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int g_loop;

static void  checker(char **save, char **cmd, t_win **win, char buf[])
{
	if (!(*win)->hd && check_quotes(cmd, win))
		(*save) = ft_strjoinf((*save), (*cmd), 1);
	if (!(*win)->quote)
		(!(*win)->hd) ? get_here_string(save, win, -1, 0) :
		heredoc(cmd, win, buf);
	if ((*save) && !(*win)->hd && !(*win)->quote)
		handle_pipe_and_or(save, win);
	if ((*save) && !(*win)->hd && !(*win)->quote && !(*win)->pao &&
	(*save)[ft_strlen((*save)) - 1] == '\\')
	{
		write(1, "\n$> ", 4);
		g_loop = 256;
		(*win)->cur = 3;
	}
	ft_memset((*cmd), 0, ft_strlen(*cmd));
	!(*win)->hd && !(*win)->quote && !(*win)->pao ? (*win)->pr = 3 : 0;
	(*win)->sh = 0;
}

static int					check_line(char **save, char **cmd, t_win **win, char buf[])
{
	if (EOT && !(*win)->hd)
	{
		save ? save_history(*win, save, &(*win)->his) : 0;
		EOT && save && ((*cmd && !(*cmd)[0]) || !(*cmd)) ? ft_strdel(save) : 0;
		EOT && cmd && ((*cmd && !(*cmd)[0]) || !(*cmd)) ? ft_strdel(cmd) : 0;
		if (EOT && (*win)->pao)
			return (fd_printf(2, "\n42sh: syntax error: unexpected end of file"));
		else if (EOT && (*win)->quote)
			return (fd_printf(2, "\n42sh: unexpected EOF while looking for matching "
			"`%c' \n42sh: syntax error: unexpected end of file",\
			(*win)->quote == 1 ? '\'' : '\"'));
		EOT && (!(*cmd) || !(*cmd)[0]) ? (*win)->ctrld = 1 : 0;
		return ((*win)->ctrld ? 1 : 0);
	}
	else if (RETURN && ((*save) || (*cmd)))
    checker(save, cmd, win, buf);
	else if (!(*save) || (!(*cmd) || !(*cmd)[0]))
    g_loop = 0;
	return (0);
}

int  check_cmdl(char **save, char **cmd, t_win **win, char buf[])
{
  if (!(*win)->sh)
  {
    if (check_line(save, cmd, win, buf))
      return (1);
  }
  else
  {
    e(win, &(*win)->his, cmd, save);
    return(1);
  }
  return (0);
}
