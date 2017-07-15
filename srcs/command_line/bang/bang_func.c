/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 14:05:48 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/13 14:05:55 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void   process_mod(char **tmp, t_bang *bang, int i, char *ptr)
{
  char        **arr;

  bang->mod & H && (ptr = ft_strchr(*tmp, '/')) ? (*ptr) = 0 : 0;
  bang->mod & RB && (ptr = ft_strchr(*tmp, '.')) ? (*ptr) = 0 : 0;
  bang->mod & Q ? (*tmp) = ft_strjoinf(ft_strjoinf("\'", (*tmp), 2), "\'", 1): 0;
  if (bang->mod & T && (ptr = ft_strchr(*tmp, '/')))
  {
    ft_strdel(tmp);
    (*tmp) = ft_strdup(ptr + 1);
  }
  if (bang->mod & E && (ptr = ft_strchr(*tmp, '.')))
  {
    ft_strdel(tmp);
    (*tmp) = ft_strdup(ptr);
  }
  if (bang->mod & X && (arr = ft_strsplit((*tmp), ' ')))
  {
    ft_strdel(tmp);
    while (arr[++i])
    {
      arr[i] = ft_strjoinf(ft_strjoinf("\'", arr[i], 2), "\'", 1);
      (*tmp) = ft_strjoinf(ft_strjoinf(*tmp, arr[i], 1), " ", 1);
    }
    ft_free(arr, NULL);
  }
}

int      mod_cmd(char **cmd, char **array, t_bang *bang)
{
  int     ret;
  char    *beg;
  char    *end;

  (*cmd)[bang->b] = 0;
  beg = ft_strdup(*cmd);
  end = ft_strdup(*cmd + bang->e);
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

static int  last_bang(char **cmd, char **buf)
{
  ft_strdel(cmd);
  *cmd = ft_strdupf(buf);
  return (1);
}

int 				fill_buf(char *tmp, char **cmd, int i, int j)
{
	static char	*buf = NULL;
	char				*sub;
	int					b;
	int					e;

  !buf ? buf = ft_strdup(*cmd) : 0;
	if (j)
    return (last_bang(cmd, &buf));
	while (buf[++i])
		if (buf[i] == '!')
		{
			b = i ;
			buf[i + 1] == '!' ? i += 1 : 0;
			while (buf[++i] && buf[i] != '<' && buf[i] != '>' && buf[i] != '\"' &&
      buf [i] != '\'' && buf[i] != ';' && buf[i] != '|' && buf[i] != '&' &&
      buf[i] != '!')
        ;
			e = i;
			sub = ft_strdup(buf + e);
			buf[b] = 0;
			buf = ft_strjoinf(ft_strjoinf(ft_strjoinf(buf, tmp, 1), " ", 1), sub, 3);
			break ;
		}
  return (0);
}
