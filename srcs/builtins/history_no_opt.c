/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_no_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:35:31 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 20:54:28 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		get_history_arg(t_ast **tmp, char **arg)
{
	if (!(*tmp)->right || !(*tmp)->right->str)
		return (0);
	*arg = ft_strdup((*tmp)->right->str);
	(*tmp) = (*tmp)->right;
	while ((*tmp)->right && (*tmp)->right->str)
	{
		*arg = ft_strjoinf(ft_strjoinf(*arg, " ", 1),
		(*tmp)->right->str, 1);
		(*tmp) = (*tmp)->right;
	}
	return (0);
}
