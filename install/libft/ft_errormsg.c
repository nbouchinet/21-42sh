/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errormsg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 09:02:55 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/06 14:18:32 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_errormsg(char *env, char *cmd, char *str)
{
	if (env)
		ft_putstr_fd(env, 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (str)
		ft_putendl_fd(str, 2);
}
