/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_no_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:35:31 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/18 16:35:41 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void    no_options(t_his **his, int offset, int len, int i)
{
  int     nbr;

  nbr = 0;
  if (i == 7 && (!offset || offset > len))
    while ((*his) && ft_strcmp((*his)->cmdl, ""))
    {
      ft_printf("    %d  %s\n", ++nbr, (*his)->cmdl);
      (*his) = (*his)->next;
    }
  else if (i == 7 && offset)
  {
    len = len - offset;
    while (--len)
    {
      (*his) = (*his)->next;
      nbr += 1;
    }
    while ((*his) && ft_strcmp((*his)->cmdl, ""))
    {
      ft_printf("    %d  %s\n", ++nbr, (*his)->cmdl);
      (*his) = (*his)->next;
    }
  }
}
