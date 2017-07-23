/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 16:31:41 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/10 16:31:42 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void   process_des_and_mod(char **array, char **tmp, t_bang *bang)
{
  ft_putnbrl(bang->mod);
  ft_putendl(*tmp);
  bang->des != -5 || bang->x ? ft_strdel(tmp) : 0;
  if (bang->des != -5)
    (*tmp) = ft_strdup(array[bang->des]);
  else if (bang->x && bang->y)
    while (bang->x <= bang->y)
      (*tmp) = ft_strjoinf(ft_strjoinf(*tmp, array[bang->x++], 1), " ", 1);
  process_mod(tmp, bang, -1, NULL);
}

static int    check_des(t_bang *bang, int len)
{
  bang->des == -1 ? bang->des = (len - 1) : 0;
  bang->y != 0 && (bang->y == -1) ? bang->y = (len - 1) : 0;
  bang->y != 0 && (bang->y == -2) ? bang->y = (len - 2) : 0;
  if ((bang->x < 0 || bang->y < 0))
    return (fd_printf(2, "\n42sh: %d: bad word specifier",
	bang->x < 0 ? bang->x : bang->y));
  else if ((bang->des && bang->des > len))
    return (fd_printf(2, "\n42sh: %d: bad word specifier", bang->des));
  else if (bang->x > len || bang->y > len)
    return (fd_printf(2, "\n42sh: %d-%d: bad word specifier",
	bang->x, bang->y));
  else if (bang->x > bang->y)
    return (fd_printf(2, "\n42sh: %d-%d: bad word specifier",
	bang->x, bang->y));
  return (0);
}

static int   get_match(t_his *his, t_bang *bang, char **tmp, char *arr)
{
  while (his->next)
    his = his->next;
  if (bang->string)
  {
    while (his)
    {
      if (arr[0] == '?' && ft_strnstr(his->cmdl, bang->string,
      ft_strlen(his->cmdl)))
      {
        *tmp = ft_strdup(his->cmdl);
        break ;
      }
      else if (ft_strnstr(his->cmdl, bang->string, ft_strlen(bang->string)))
      {
        *tmp = ft_strdup(his->cmdl);
        break ;
      }
      his = his->prev;
    }
  }
  else
    *tmp = ft_strdup(his->prev->cmdl);
  return (*tmp ? 0 : fd_printf(2, "\n42sh: !%s: event not found", arr));
}

static int   get_line(t_his *his, t_bang *bang, char **tmp)
{
  if (bang->n > 0)
    while (his->next && bang->n--)
      his = his->next;
  else
  {
    while (his->next)
      his = his->next;
    his = his->prev;
    while (his->prev && bang->n++ < 0)
      his = his->prev;
  }
  (*tmp) = ft_strdup(his->cmdl);
  return (*tmp ? 0 : 1);
}

int           do_sub(t_his *his, t_bang *bang, char **cmd, char *arr)
{
  char      **array;
  char      *tmp;
  int       ret;

  tmp = NULL;
  ret = bang->n ? get_line(his, bang, &tmp) : get_match(his, bang, &tmp, arr);
  if (ret)
    return (1);
  array = ft_strsplit(tmp, ' ');
  if (check_des(bang, ft_tablen(array)))
    return (1);
  !bang->s1 ? process_des_and_mod(array, &tmp, bang) : 0;
  !bang->s1 ? fill_buf(tmp, cmd, -1, 0) : 0;
  bang->s1 ? ret = mod_cmd(cmd, array, bang) : 0;
  ft_free(array, &tmp);
  return (bang->s1 ? ret : 0);
}
