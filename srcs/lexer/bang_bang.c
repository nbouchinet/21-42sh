/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_bang.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 18:20:41 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/08 18:20:52 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int    get_modifiers(char *arr, t_bang *bang)
{
  arr[0] == 'h' ? bang->mod |= H : 0;
  arr[0] == 't' ? bang->mod |= T : 0;
  arr[0] == 'r' ? bang->mod |= RB : 0;
  arr[0] == 'e' ? bang->mod |= E : 0;
  arr[0] == 'p' ? bang->mod |= PB : 0;
  arr[0] == 'q' ? bang->mod |= Q : 0;
  arr[0] == 'x' ? bang->mod |= X : 0;
  if (!ft_strchr("htrepqx", arr[0]))
    return (fd_printf(2, "unrecognized history modifier\n"));
  return (0);
}

static int    get_designators(char *arr, t_bang *bang)
{
    char      **sub;

    if (arr[0] >= '0' && arr[0] <= '9' && !ft_strchr(arr, '-') &&
    !ft_strchr(arr, '*'))
      bang->des = ft_atoi(arr);
    else if (arr[0] == '^')
      bang->des = 1;
    else if (arr[0] == '$')
      bang->des = -1;
    else if (ft_strchr(arr, '-'))
    {
      sub = ft_strsplit(arr, '-');
      bang->x = ft_atoi(sub[0]);
      bang->y = sub[1] ? ft_atoi(sub[1]) : -2;
      ft_free(sub, NULL);
    }
    else if (ft_strchr(arr, '*'))
    {
      bang->x = arr[0] == '*' ? 1 : ft_atoi(arr);
      bang->y = -1;
    }
    else
      return (fd_printf(2, "42sh: !%s: event not found\n", arr));
    return (0);
}

static int    get_event(char *arr, t_bang *bang, t_his *his)
{
    char      **sub;

    if (arr[0] >= '0' && arr[0] <= '9')
      bang->n = ft_atoi(arr) - 1;
    else if (arr[0] == '-' && arr[1] && arr[1] >= '0' && arr[1] <= '9')
    bang->n = (ft_atoi(arr + 1) - 1) * -1;
    else if (arr[0] == '!')
      bang->n = 0;
    else if (arr[0] == '?')
      bang->string = arr + 1;
    else if (arr[0] == '^')
    {
      sub = ft_strsplit(arr, '^');
      bang->s1 = ft_strdup(sub[0]);
      bang->s2 = ft_strdup(sub[1]);
      ft_free(sub, NULL);
    }
    else if (ft_isalpha(arr[0]))
      bang->string = arr;
    else
      return (fd_printf(2, "42sh: !%s: event not found\n", arr));
    if (bang->n && (bang->n < 0 ? -bang->n : bang->n) > lst_len(his))
      return (fd_printf(2, "\n42sh: !%d: no such event", bang->n));
    return (0);
}

int           bang_bang(char **cmd, char *str, t_bang *bang)
{
  t_his       *his;
  char        **array;
  int         len;

  his = win_sgt()->his;
  if (!his->prev)
    return (fd_printf(2, "\n42sh: %c%c: event not found", str[0], str[1]));
  while (his->prev)
    his = his->prev;
  array = ft_strsplit(str, ':');
  len = ft_tablen(array);
  if (0 < len && get_event(array[0], bang, his))
  {
    ft_free(array, &str);
    return (1);
  }
  if (1 < len && get_designators(array[1], bang))
    return (ft_free(array, &str));
  if (2 < len && get_modifiers(array[2], bang))
    return (ft_free(array, &str));
  if ((len = do_sub(his, bang, cmd, array[0])))
    return (len == 2 ? ft_free(array, &str) + 1 : ft_free(array, &str));
  ft_free(array, &str);
  return (0);
}
