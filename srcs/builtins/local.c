/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 16:56:27 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/15 16:56:42 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int 		check_local(t_ast *tmp, int type)
{
	if (type != PIPE_SEQ && ft_strchr(tmp->left->left->str, '='))
		return (local(tmp->left->left->str));
	else if (type == PIPE_SEQ && tmp->right->left->left->left->str &&
	ft_strchr(tmp->right->left->left->left->str, '='))
		return (local(tmp->right->left->left->left->str));
	else if (type == PIPE_SEQ && tmp->right->right->left->left->str &&
	ft_strchr(tmp->right->right->left->left->str, '='))
		return (local(tmp->right->right->left->left->str));
	return (0);
}

t_local		**local_sgt(int i)
{
	static t_local *loc = NULL;

	if (!loc && i == 1)
	{
		if (!(loc = (t_local*)malloc(sizeof(t_local))))
			exit(fd_printf(2, "malloc error\n"));
    loc->var = NULL;
    loc->val = NULL;
    loc->n = NULL;
		return (&loc);
	}
	return (&loc);
}

static void stock_loc(int match, char **arr, t_local *loc)
{
  if (match)
  {
    if (!(loc->n = (t_local*)malloc(sizeof(t_local))))
      exit(fd_printf(2, "malloc error\n"));
    loc->n->var = ft_strdup(arr[0]);
    loc->n->val = ft_strdup(arr[1]);
    loc->n->n = NULL;
  }
  else
  {
    loc->var = ft_strdups(arr[0], &loc->var);
    loc->val = ft_strdups(arr[1], &loc->val);
  }
}

int   local(char *str)
{
  t_local   *loc;
  char      **arr;
  int       match;

  loc = *local_sgt(1);
  arr = ft_strsplit(str, '=');
  match = 0;
  if (!loc->var)
  {
    loc->var = ft_strdup(arr[0]);
    loc->val = ft_strdup(arr[1]);
    ft_free(arr, NULL);
    return (1);
  }
  while ((match = ft_strcmp(loc->var, arr[0])) && loc->n)
    loc = loc->n;
  stock_loc(match, arr, loc);
  ft_free(arr, NULL);
  return (1);
}
