/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_no_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:35:31 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 08:51:44 by nbouchin         ###   ########.fr       */
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
      (*his) = (*his)->n;
    }
  else if (i == 7 && offset)
  {
    len = len - offset;
    while (--len)
    {
      (*his) = (*his)->n;
      nbr += 1;
    }
    while ((*his) && ft_strcmp((*his)->cmdl, ""))
    {
      ft_printf("    %d  %s\n", ++nbr, (*his)->cmdl);
      (*his) = (*his)->n;
    }
  }
}
