/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 14:57:54 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/24 13:46:07 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		print_prompt(t_env *env)
{
	char	buff[1024];

	if (env)
		ft_printf("%@42sh: %s%@\n$> ", H_YELLOW, lst_at(&env, "PWD")->value, I);
	else
	{
		getcwd(buff, 1024);
		ft_printf("%@42sh: %s%@\n$> ", H_YELLOW, buff, I);
	}
}
