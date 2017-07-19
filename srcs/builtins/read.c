/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 13:26:01 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/18 13:26:09 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void   buf_save(char **stack, char buf[], int *i, int type)
{
  char *tmp;
  static int len = 512;

  if ((*i) == len)
  {
    tmp = *stack;
    if (!((*stack) = (char *)malloc(sizeof(char) * (len + 512))))
      exit(fd_printf(2, "malloc error\n"));
    (*stack) = ft_strcpy((*stack), tmp);
    (*stack) = ft_strcat((*stack), buf);
    (*i) += 1;
    len += 512;
  }
  else
    (*stack)[++(*i)] = !type ? buf[0] : 0;
}

static void   read_input(void)
{
  char buf[3];
  char *stack;
  int  i;

  stack = ft_memalloc(512);
  i = -1;
  while (1)  // -t <timeout>, -n <nchars>
  {
    ft_memset(buf, '\0', 3);
    read(0, buf, 1); //-u <fd>
    if (PRINT)
      buf_save(&stack, buf, &i, 0);
    if (RETURN) // -d <delimiter>, '\' esc char,
    {
      buf_save(&stack, buf, &i, 1);
      break ;
    }
  }
  ft_printf("\n%@%s%@\n", GREEN, stack, I);
}

static int  get_opt(t_read *var, char **targ, int *i)
{

}

int         ft_read(t_ast **ast, t_env **env)
{
  t_read  var;
  char    **targ;
  int     i;

  (void)env;
  ft_memset(&var, 0, sizeof(var));
  targ = creat_arg_env(&(*ast)->left->right);
  i = 0;
  if (targ && get_opt(&var, targ, &i))
    return (0);
  read_input();
  return (1);
}
